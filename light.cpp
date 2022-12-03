#pragma once
#include "light.h"
#include "graphic.h"

bool Light::init(IDirect3DDevice9* device, const D3DLIGHT9& light, float radius, DWORD& index)
{
	if (NULL == device)
		return false;

	ID3DXMesh* sphereMesh;
	if (FAILED(D3DXCreateSphere(device, radius, 10, 10, &sphereMesh, NULL)))
		return false;
	setMesh(sphereMesh);

    this->index = index;
	this->radius = radius;

	setPosition(light.Position);

	this->light.Type = light.Type;
    this->light.Diffuse = light.Diffuse;
    this->light.Specular = light.Specular;
    this->light.Ambient = light.Ambient;
    this->light.Position = light.Position;
    this->light.Direction = light.Direction;
    this->light.Range = light.Range;
    this->light.Falloff = light.Falloff;
    this->light.Attenuation0 = light.Attenuation0;
    this->light.Attenuation1 = light.Attenuation1;
    this->light.Attenuation2 = light.Attenuation2;
    this->light.Theta = light.Theta;
    this->light.Phi = light.Phi;

    setMaterial(Graphic::WHITE, 2.0f);
    
    index++;
    return true;
}

bool Light::setLight(IDirect3DDevice9* device, const D3DXMATRIX& worldMatrix)
{
    if (NULL == device)
        return false;

    D3DXVECTOR3 position = getPosition();
    D3DXVec3TransformCoord(&position, &position, &worldMatrix);

    light.Position = position;

    device->SetLight(index, &light);
    device->LightEnable(index, TRUE);

    return true;
}

void Light::response(Object* object)
{
    
}