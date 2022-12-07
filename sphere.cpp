#include "sphere.h"
#include "scene.h"
#include "cuboid.h"
#include "physics.h"

#include <iostream>

#include <cmath>

bool Sphere::init(IDirect3DDevice9* device, D3DXCOLOR color, float radius)
{
	if (NULL == device)
		return false;

	this->radius = radius;
	setShape(SPHERE);

	setMaterial(color, 5.0f);

	ID3DXMesh* sphereMesh;
	if (FAILED(D3DXCreateSphere(device, radius, 50, 50, &sphereMesh, NULL)))
		return false;
	setMesh(sphereMesh);

	return true;
}

bool Sphere::collideWith(const Object* object) const
{
	Shape targetShape = object->getShape();

	if (targetShape == CUBOID)
	{
		const Cuboid* cuboid = dynamic_cast<const Cuboid*>(object);
		return Physics::checkCollision(this, cuboid);
	}

	if (targetShape == SPHERE)
	{
		const Sphere* sphere = dynamic_cast<const Sphere*>(object);
		return Physics::checkCollision(this, sphere);
	}

	return false;
}

void Sphere::response(Object* object)
{
	Shape targetShape = object->getShape();

	if (targetShape == CUBOID)
	{
		Cuboid* cuboid = dynamic_cast<Cuboid*>(object);
		Physics::responseCollision(this, cuboid);
		return;
	}

	if (targetShape == SPHERE)
	{
		Sphere* sphere = dynamic_cast<Sphere*>(object);
		Physics::responseCollision(this, sphere);
		return;
	}
}