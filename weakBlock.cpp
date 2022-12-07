#include "weakBlock.h"
#include "graphic.h"

bool WeakBlock::init(IDirect3DDevice9* device, D3DXVECTOR3 position)
{
	size.x = 1.6f;
	size.y = 0.2f;
	size.z = 1.6f;

	setPosition(position);
	setStatic();
	setShape(CUBOID);

	if (NULL == device)
		return false;

	setMaterial(Graphic::BROWN, 5.0f);

	ID3DXMesh* cuboidMesh;
	if (FAILED(D3DXCreateBox(device, size.x, size.y, size.z, &cuboidMesh, NULL)))
		return false;
	setMesh(cuboidMesh);

	return true;
}

void WeakBlock::onCollide(Object* target)
{
	setRenderOnly();
	setInvisible();
}