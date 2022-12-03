#include "line.h"
#include "sphere.h"
#include "physics.h"

bool Line::init(
	IDirect3DDevice9* device, 
	D3DXCOLOR color, 
	float length, 
	float width
)
{
	if (NULL == device)
		return false;

	setMaterial(color, 5.0f);

	this->length = length;
	this->width = width;

	ID3DXMesh* boxMesh;
	if (FAILED(D3DXCreateBox(device, length, 0.1f, width, &boxMesh, NULL)))
		return false;
	setMesh(boxMesh);

	return true;
}

bool Line::collideWith(const Object* object) const
{

	Shape targetShape = object->getShape();

	if (targetShape == SPHERE)
	{
		const Sphere* sphere = dynamic_cast<const Sphere*>(object);
		return Physics::checkCollision(this, sphere);
	}

	return false;
}

void Line::response(Object* object)
{
	Shape targetShape = object->getShape();

	if (targetShape == SPHERE)
	{
		Sphere* sphere = dynamic_cast<Sphere*>(object);
		Physics::responseCollision(this, sphere);
		return;
	}

	return;
}