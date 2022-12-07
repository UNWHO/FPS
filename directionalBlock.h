#pragma once
#include "cuboid.h"

class DirectionalBlock : public Cuboid
{
private:
	D3DXVECTOR3 startPosition;
	float distanceSq;

	float speed;

public:
	bool init(IDirect3DDevice9* device, D3DXVECTOR3 startPosition, D3DXVECTOR3 direction, float speed);

	virtual void onBeforeRender();
};