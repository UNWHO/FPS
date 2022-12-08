#pragma once
#include "cuboid.h"

class StaticBlock : public Cuboid
{
public:
	bool init(IDirect3DDevice9* device, D3DXVECTOR3 position, D3DXVECTOR3 size);
};

