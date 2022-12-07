#pragma once
#include "cuboid.h"

class WeakBlock : public Cuboid
{
public:
	bool init(IDirect3DDevice9* device, D3DXVECTOR3 position);

	virtual void onCollide();
};