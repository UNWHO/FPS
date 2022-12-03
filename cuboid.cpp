#include "cuboid.h"
#include "sphere.h"
#include "physics.h"

bool Cuboid::init(IDirect3DDevice9* device, const D3DXVECTOR3& size, D3DXCOLOR color)
{
	if (NULL == device)
		return false;

	setMaterial(color, 5.0f);

	this->size.x = size.x;
	this->size.y = size.y;
	this->size.z = size.z;

	ID3DXMesh* cuboidMesh;
	if (FAILED(D3DXCreateBox(device, size.x, size.y, size.z, &cuboidMesh, NULL)))
		return false;
	setMesh(cuboidMesh);

	return true;
}


bool Cuboid::collideWith(const Object* object) const
{
	Shape targetShape = object->getShape();

	if (targetShape == SPHERE)
	{
		const Sphere* sphere = dynamic_cast<const Sphere*>(object);
		return Physics::checkCollision(sphere, this);
	}

	return false;
}

void Cuboid::response(Object* object)
{
	Shape targetShape = object->getShape();

	if (targetShape == SPHERE)
	{
		Sphere* sphere = dynamic_cast<Sphere*>(object);
		Physics::responseCollision(sphere, this);
		return;
	}
}