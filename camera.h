#pragma once
#include <d3dx9.h>
#include "object.h"

class Camera
{
private:
	IDirect3DDevice9* device;
	Object* target;

	const float distance = 1.5f;
	bool perspective = true;

	
	D3DXVECTOR3 cameraDirection;
	D3DXVECTOR3 cameraPosition;
	D3DXMATRIX viewMatrix;

public:
	void init(IDirect3DDevice9* device) { this->device = device; };
	void attach(Object* target) { this->target = target; };
	void update();
};