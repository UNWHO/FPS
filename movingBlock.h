#pragma once
#include "cuboid.h"

class MovingBlock : public Cuboid
{
private:
	D3DXVECTOR3 startPosition;
	D3DXVECTOR3 arrivalPosition;
	float distanceSq;

	float speed;
	bool direction;

public:
	bool init(IDirect3DDevice9* device, D3DXVECTOR3 startPosition, D3DXVECTOR3 arrivalPosition, float speed);

	virtual void onBeforeRender();
};