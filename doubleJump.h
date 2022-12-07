#pragma once
#include "sphere.h"

class DoubleJump : public Sphere
{
public:
	bool init(IDirect3DDevice9* device, D3DXVECTOR3 position);

	virtual void onCollide(Object*);
};