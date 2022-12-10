#include <cmath>
#include "physics.h"
#include <iostream>
#include <cassert>

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

	return true;
}

// modified for project4
bool Physics::checkCollision(const Cuboid* cuboid_A, const Cuboid* cuboid_B)
{
	if (cuboid_A->isRenderOnly() || cuboid_B->isRenderOnly())
		return false;

	D3DXVECTOR3 cuboid_ASize = cuboid_A->getSize();
	D3DXVECTOR3 cuboid_BSize = cuboid_B->getSize();
	cuboid_ASize /= 2;
	cuboid_BSize /= 2;

	D3DXVECTOR3 cuboid_APosition = cuboid_A->getPosition();
	D3DXVECTOR3 cuboid_BPosition = cuboid_B->getPosition();

	if (cuboid_APosition.x + cuboid_ASize.x < cuboid_BPosition.x - cuboid_BSize.x) return false;
	if (cuboid_APosition.x - cuboid_ASize.x > cuboid_BPosition.x + cuboid_BSize.x) return false;
	if (cuboid_APosition.y + cuboid_ASize.y < cuboid_BPosition.y - cuboid_BSize.y) return false;
	if (cuboid_APosition.y - cuboid_ASize.y > cuboid_BPosition.y + cuboid_BSize.y) return false;
	if (cuboid_APosition.z + cuboid_ASize.z < cuboid_BPosition.z - cuboid_BSize.z) return false;
	if (cuboid_APosition.z - cuboid_ASize.z > cuboid_BPosition.z + cuboid_BSize.z) return false;
	
	return true;
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

	D3DXVECTOR3 relativeVelocity = sphereVelocity - cuboidVelocity;

	if (cuboid->isStatic())
	{
		D3DXVECTOR3 offset = { 0.0f, 0.0f, 0.0f };

		if (relativeVelocity.x > 0)
			offset.x = (spherePosition.x + radius) - (cuboidPosition.x - cuboidSize.x);
		else
			offset.x = (spherePosition.x - radius) - (cuboidPosition.x + cuboidSize.x);

		if (relativeVelocity.y > 0)
			offset.y = (spherePosition.y + radius) - (cuboidPosition.y - cuboidSize.y);
		else
			offset.y = (spherePosition.y - radius) - (cuboidPosition.y + cuboidSize.y);

		if (relativeVelocity.z > 0)
			offset.z = (spherePosition.z + radius) - (cuboidPosition.z - cuboidSize.z);
		else
			offset.z = (spherePosition.z - radius) - (cuboidPosition.z + cuboidSize.z);


		enum dir { DIR_X, DIR_Y, DIR_Z} dir;

		if (0 == relativeVelocity.x) relativeVelocity.x = 0.0000001f;
		if (0 == relativeVelocity.y) relativeVelocity.y = 0.0000001f;
		if (0 == relativeVelocity.z) relativeVelocity.z = 0.0000001f;

		if (std::fabs(offset.x / relativeVelocity.x) <= std::fabs(offset.y / relativeVelocity.y))
		{
			if (std::fabs(offset.x / relativeVelocity.x) <= std::fabs(offset.z / relativeVelocity.z)) dir = DIR_X;
			else dir = DIR_Z;
		}
		else
		{
			if (std::fabs(offset.y / relativeVelocity.y) <= std::fabs(offset.z / relativeVelocity.z)) dir = DIR_Y;
			else dir = DIR_Z;
		}
		

		D3DXVECTOR3 normVelocitiy;
		D3DXVec3Normalize(&normVelocitiy, &relativeVelocity);

		float length;
		
		switch (dir)
		{
		case DIR_X:
			length = offset.x / normVelocitiy.x + Physics::RESPONSE_OFFSET;
			normVelocitiy.x = -normVelocitiy.x;
			sphere->setVelocity({ 0.0f, sphereVelocity.y, sphereVelocity.z });
			break;
		case DIR_Y:
			length = offset.y / normVelocitiy.y + Physics::RESPONSE_OFFSET;
			normVelocitiy.y = -normVelocitiy.y;
			sphere->setVelocity({ sphereVelocity.x, 0.0f,sphereVelocity.z });
			break;
		case DIR_Z:
			length = offset.z / normVelocitiy.z + Physics::RESPONSE_OFFSET;
			normVelocitiy.z = -normVelocitiy.z;
			sphere->setVelocity({ sphereVelocity.x, sphereVelocity.y, 0.0f });
		}
		D3DXVECTOR3 newPos = spherePosition + normVelocitiy * length;
		assert(!std::isnan(newPos.x) && !std::isnan(newPos.y) && !std::isnan(newPos.z));
		sphere->setPosition(spherePosition + normVelocitiy * length);
	}
}

// modified for project4
// need modify
void Physics::responseCollision(Cuboid* cuboid_A, Cuboid* cuboid_B)
{
	return;
	enum shape { WALL, BLOCK };
	enum shape type_A, type_B;

	if (cuboid_A->isStatic()) {
		type_A = WALL;
		type_B = BLOCK;
	}
	else {
		type_A = BLOCK;
		type_B = WALL;
	}

	enum dir { HORIZONTAL, VERTICAL } dir = VERTICAL;
	D3DXVECTOR3 offset = { 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3 normVelocitiy;
	float length;

	D3DXVECTOR3 cuboid_AVelocity = cuboid_A->getVelocity();
	D3DXVECTOR3 cuboid_APosition = cuboid_A->getPosition();
	D3DXVECTOR3 cuboid_ASize = cuboid_A->getSize();
	cuboid_ASize /= 2;

	D3DXVECTOR3 cuboid_BVelocity = cuboid_B->getVelocity();
	D3DXVECTOR3 cuboid_BPosition = cuboid_B->getPosition();
	D3DXVECTOR3 cuboid_BSize = cuboid_B->getSize();
	cuboid_BSize /= 2;

	switch (type_A) {
	case(WALL):
		if (cuboid_BVelocity.x > 0)
			offset.x = (cuboid_BPosition.x + cuboid_BSize.x) - (cuboid_BPosition.x - cuboid_BSize.x);
		else
			offset.x = (cuboid_BPosition.x - cuboid_BSize.x) - (cuboid_BPosition.x + cuboid_BSize.x);

		if (cuboid_BVelocity.z > 0)
			offset.z = (cuboid_BPosition.z + cuboid_BSize.z) - (cuboid_BPosition.z - cuboid_BSize.z);
		else
			offset.z = (cuboid_BPosition.z - cuboid_BSize.z) - (cuboid_BPosition.z + cuboid_BSize.z);

		if (cuboid_BVelocity.x == 0)
			dir = VERTICAL;
		else if (cuboid_BVelocity.z == 0)
			dir = HORIZONTAL;
		else {
			if (std::fabs(offset.x / cuboid_BVelocity.x) < std::fabs(offset.z / cuboid_BVelocity.z))
				dir = HORIZONTAL;
			else dir = VERTICAL;
		}

		D3DXVec3Normalize(&normVelocitiy, &cuboid_BVelocity);

		switch (dir) {
		case HORIZONTAL:
			length = offset.x / normVelocitiy.x + Physics::RESPONSE_OFFSET;
			cuboid_B->setVelocity({ -cuboid_BVelocity.x,cuboid_BVelocity.y,cuboid_BVelocity.z });
			break;
		case VERTICAL:
			length = offset.z / normVelocitiy.z + Physics::RESPONSE_OFFSET;
			cuboid_B->setVelocity({ cuboid_BVelocity.x,cuboid_BVelocity.y,-cuboid_BVelocity.z });
			break;
		}
		cuboid_B->setPosition(cuboid_BPosition - normVelocitiy * length);

	case(BLOCK):
		if (cuboid_AVelocity.x > 0)
			offset.x = (cuboid_APosition.x + cuboid_ASize.x) - (cuboid_APosition.x - cuboid_ASize.x);
		else
			offset.x = (cuboid_APosition.x - cuboid_ASize.x) - (cuboid_APosition.x + cuboid_ASize.x);

		if (cuboid_AVelocity.z > 0)
			offset.z = (cuboid_APosition.z + cuboid_ASize.z) - (cuboid_APosition.z - cuboid_ASize.z);
		else
			offset.z = (cuboid_APosition.z - cuboid_ASize.z) - (cuboid_APosition.z + cuboid_ASize.z);

		if (cuboid_AVelocity.x == 0)
			dir = VERTICAL;
		else if (cuboid_AVelocity.z == 0)
			dir = HORIZONTAL;
		else {
			if (std::fabs(offset.x / cuboid_AVelocity.x) < std::fabs(offset.z / cuboid_AVelocity.z))
				dir = HORIZONTAL;
			else dir = VERTICAL;
		}

		D3DXVec3Normalize(&normVelocitiy, &cuboid_AVelocity);

		switch (dir) {
		case HORIZONTAL:
			length = offset.x / normVelocitiy.x + Physics::RESPONSE_OFFSET;
			cuboid_A->setVelocity({ -cuboid_AVelocity.x,cuboid_AVelocity.y,cuboid_AVelocity.z });
			break;
		case VERTICAL:
			length = offset.z / normVelocitiy.z + Physics::RESPONSE_OFFSET;
			cuboid_A->setVelocity({ cuboid_AVelocity.x,cuboid_AVelocity.y,-cuboid_AVelocity.z });
			break;
		}
		cuboid_A->setPosition(cuboid_APosition - normVelocitiy * length);
	}
}