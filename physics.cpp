#include <cmath>
#include "physics.h"
#include <iostream>

// modified for project4
bool Physics::checkCollision(const Sphere* sphere_A, const Sphere* sphere_B)
{
	if (sphere_A->isRenderOnly() || sphere_B->isRenderOnly())
		return false;

	float radiusSum = sphere_A->getRadius() + sphere_B->getRadius();

	D3DXVECTOR3 distance = sphere_A->getPosition() - sphere_B->getPosition();

	return distance.x * distance.x + distance.y * distance.y + distance.z * distance.z < radiusSum* radiusSum;
}

// modified for project4
bool Physics::checkCollision(const Sphere* sphere, const Cuboid* cuboid)
{
	if (sphere->isRenderOnly() || cuboid->isRenderOnly())
		return false;


	D3DXVECTOR3 cuboidSize = cuboid->getSize();
	cuboidSize /= 2;

	float radius = sphere->getRadius();

	D3DXVECTOR3 spherePosition = sphere->getPosition();
	D3DXVECTOR3 cuboidPosition = cuboid->getPosition();

	D3DXVECTOR3 distance = spherePosition - cuboidPosition;
	D3DXVECTOR3 absDistance = { abs(distance.x), abs(distance.y), abs(distance.z) };

	if (absDistance.x > cuboidSize.x + radius) return false;
	if (absDistance.y > cuboidSize.y + radius) return false;
	if (absDistance.z > cuboidSize.z + radius) return false;

	// sphere in cuboid
	if (absDistance.x > cuboidSize.x) return true;
	if (absDistance.y > cuboidSize.y) return true;
	if (absDistance.z > cuboidSize.z) return true;

	return D3DXVec3LengthSq(&(absDistance - cuboidSize)) < radius * radius;
}

bool Physics::checkCollision(const Line* line, const Sphere* sphere)
{
	if (line->isRenderOnly() || sphere->isRenderOnly())
		return false;

	D3DXVECTOR3 linePosition = line->getPosition();
	D3DXVECTOR3 spherePosition = sphere->getPosition();

	float angle = line->getAngleY();
	D3DXVECTOR3 lineDir = { std::cosf(angle), 0, -std::sinf(angle) };
	D3DXVECTOR3 distance = spherePosition - linePosition;
	D3DXVECTOR3 normDistance;
	D3DXVec3Normalize(&normDistance, &distance);

	float cosine = D3DXVec3Dot(&lineDir, &normDistance);


	if (cosine > 1.01f || cosine < 0.99f) return false;


	float length = line->getLength() / 2;
	float radius = sphere->getRadius();

	return D3DXVec3LengthSq(&distance) < (length + radius) * (length + radius);
}

// modified for project4
// velocity after collision is related with each mass
// mass is in propotion to radius squared
void Physics::responseCollision(Sphere* sphere_A, Sphere* sphere_B)
{
	float radius_A = sphere_A->getRadius();
	float radius_B = sphere_B->getRadius();

	float mass_A = radius_A * radius_A;
	float mass_B = radius_B * radius_B;

	D3DXVECTOR3 velocity_A = sphere_A->getVelocity();
	D3DXVECTOR3 velocity_B = sphere_B->getVelocity();

	D3DXVECTOR3 position_A = sphere_A->getPosition();
	D3DXVECTOR3 position_B = sphere_B->getPosition();

	D3DXVECTOR3 distance = position_A - position_B;
	D3DXVECTOR3 normDistance;
	D3DXVec3Normalize(&normDistance, &distance);

	D3DXVECTOR3 center = (position_A + position_B) / 2;

	sphere_A->setPosition(center + normDistance * radius_A);
	sphere_B->setPosition(center - normDistance * radius_B);

	float projVelocity_A = D3DXVec3Dot(&velocity_A, &normDistance);
	float projVelocity_B = D3DXVec3Dot(&velocity_B, &normDistance);

	float responseProjVelocity_A = ((mass_A - mass_B) * projVelocity_A + 2 * mass_B * projVelocity_B) / (mass_A + mass_B);
	float responseProjVelocity_B = ((mass_B - mass_A) * projVelocity_B + 2 * mass_A * projVelocity_A) / (mass_A + mass_B);

	D3DXVECTOR3 responseVelocity_A = velocity_A + (responseProjVelocity_A - projVelocity_A) * normDistance;
	D3DXVECTOR3 responseVelocity_B = velocity_B + (responseProjVelocity_B - projVelocity_B) * normDistance;

	sphere_A->setVelocity(responseVelocity_A);
	sphere_B->setVelocity(responseVelocity_B);
}

// modified for project4
void Physics::responseCollision(Sphere* sphere, Cuboid* cuboid)
{
	D3DXVECTOR3 sphereVelocity = sphere->getVelocity();
	D3DXVECTOR3 cuboidVelocity = cuboid->getVelocity();

	D3DXVECTOR3 spherePosition = sphere->getPosition();
	D3DXVECTOR3 cuboidPosition = cuboid->getPosition();

	float radius = sphere->getRadius();
	D3DXVECTOR3 cuboidSize = cuboid->getSize();
	cuboidSize /= 2;

	if (cuboid->isStatic())
	{
		D3DXVECTOR3 offset = { 0.0f, 0.0f, 0.0f };

		if (sphereVelocity.x > 0)
			offset.x = (spherePosition.x + radius) - (cuboidPosition.x - cuboidSize.x);
		else
			offset.x = (spherePosition.x - radius) - (cuboidPosition.x + cuboidSize.x);

		if (sphereVelocity.y > 0)
			offset.y = (spherePosition.y + radius) - (cuboidPosition.y - cuboidSize.y);
		else
			offset.y = (spherePosition.y - radius) - (cuboidPosition.y + cuboidSize.y);

		if (sphereVelocity.z > 0)
			offset.z = (spherePosition.z + radius) - (cuboidPosition.z - cuboidSize.z);
		else
			offset.z = (spherePosition.z - radius) - (cuboidPosition.z + cuboidSize.z);


		enum dir { HORIZONTAL_X, HORIZONTAL_Y, VERTICAL } dir = VERTICAL;

		if (sphereVelocity.x == 0 && sphereVelocity.y == 0)
			dir = VERTICAL;
		else if (sphereVelocity.y == 0 && sphereVelocity.z == 0)
			dir = HORIZONTAL_X;
		else if (sphereVelocity.z == 0 && sphereVelocity.x == 0)
			dir = HORIZONTAL_Y;
		else
		{
			if (std::fabs(offset.x / sphereVelocity.x) < std::fabs(offset.z / sphereVelocity.z) &&
				std::fabs(offset.y / sphereVelocity.y) < std::fabs(offset.z / sphereVelocity.z))
			{
				if (std::fabs(offset.x / sphereVelocity.x) < std::fabs(offset.y / sphereVelocity.y))
					dir = HORIZONTAL_X;
				else dir = HORIZONTAL_Y;
			}
			else if (std::fabs(offset.y / sphereVelocity.y) < std::fabs(offset.x / sphereVelocity.x) &&
				std::fabs(offset.z / sphereVelocity.z) < std::fabs(offset.x / sphereVelocity.x)) 
			{
				if (std::fabs(offset.y / sphereVelocity.y) < std::fabs(offset.z / sphereVelocity.z))
					dir = HORIZONTAL_Y;
				else dir = VERTICAL;
			}
			else if (std::fabs(offset.x / sphereVelocity.x) < std::fabs(offset.y / sphereVelocity.y) &&
				std::fabs(offset.z / sphereVelocity.z) < std::fabs(offset.y / sphereVelocity.y))
			{
				if (std::fabs(offset.x / sphereVelocity.x) < std::fabs(offset.z / sphereVelocity.z))
					dir = HORIZONTAL_X;
				else dir = VERTICAL;
			}
			else
				dir = VERTICAL;
		}

		D3DXVECTOR3 normVelocitiy;
		D3DXVec3Normalize(&normVelocitiy, &sphereVelocity);

		float length;

		switch (dir)
		{
		case HORIZONTAL_X:
			length = offset.x / normVelocitiy.x + Physics::RESPONSE_OFFSET;
			sphere->setVelocity({ -sphereVelocity.x, sphereVelocity.y, sphereVelocity.z });
			break;
		case HORIZONTAL_Y:
			length = offset.y / normVelocitiy.y + Physics::RESPONSE_OFFSET;
			sphere->setVelocity({ sphereVelocity.x,-sphereVelocity.y,sphereVelocity.z });
			break;
		case VERTICAL:
			length = offset.z / normVelocitiy.z + Physics::RESPONSE_OFFSET;
			sphere->setVelocity({ sphereVelocity.x, sphereVelocity.y, -sphereVelocity.z });
		}

		sphere->setPosition(spherePosition - normVelocitiy * length);
	}
}

void Physics::responseCollision(Line* line, Sphere* sphere)
{
	D3DXVECTOR3 linePosition = line->getPosition();
	D3DXVECTOR3 spherePosition = sphere->getPosition();

	D3DXVECTOR3 distance = spherePosition - linePosition;
	D3DXVECTOR3 normDistance;
	D3DXVec3Normalize(&normDistance, &distance);

	float length = line->getLength();
	float radius = sphere->getRadius();

	line->setPosition(spherePosition - normDistance * (length / 2 + radius));


	sphere->setVelocity(line->getVelocity());
	line->setVelocity({ 0.0f, 0.0f, 0.0f });
}