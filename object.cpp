#include <cstdlib>

#include "object.h"
#include "graphic.h"

#define GRAVITY 0.05;

void Object::setPosition(const D3DXVECTOR3& position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;
	
	updateLocalMatrix();
}

void  Object::update(float deltaTime)
{
	if (this->staticFlag) return;

	if(this->gravity)
		velocity.y -= GRAVITY;

	setPosition(position + 3.3f * deltaTime * velocity);
}

void Object::render(IDirect3DDevice9* device, const D3DXMATRIX& worldMatrix)
{
	if (NULL == device)
		return;

	if (!visible)
		return;

	device->SetTransform(D3DTS_WORLD, &worldMatrix);
	device->MultiplyTransform(D3DTS_WORLD, &localMatrix);
	device->SetMaterial(&material);
	mesh->DrawSubset(0);
}

void Object::setMaterial(D3DXCOLOR color, float power)
{
	material.Ambient = color;
	material.Diffuse = color;
	material.Specular = color;
	material.Emissive = Graphic::BLACK;
	material.Power = power;
}

void Object::rotate(const D3DXVECTOR3& angle)
{
	this->angle = angle;

	updateLocalMatrix();
}

void Object::rotateY(float angle)
{
	this->angle.y = angle;

	updateLocalMatrix();
}

void Object::updateLocalMatrix()
{
	D3DXMATRIX traslation;
	D3DXMatrixTranslation(&traslation, position.x, position.y, position.z);

	D3DXMATRIX rotationX, rotationY, rotationZ;
	D3DXMatrixRotationX(&rotationX, angle.x);
	D3DXMatrixRotationY(&rotationY, angle.y);
	D3DXMatrixRotationZ(&rotationZ, angle.z);

	localMatrix = rotationZ * rotationY * rotationX * traslation;
}