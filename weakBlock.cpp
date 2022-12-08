#include "weakBlock.h"
#include "graphic.h"
#include "player.h"

bool WeakBlock::init(IDirect3DDevice9* device, D3DXVECTOR3 position)
{
	size.x = 2.0f;
	size.y = 0.2f;
	size.z = 2.0f;

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
	if(dynamic_cast<PlayerFoot*>(target) == NULL)
		return;

	setRenderOnly();
	setInvisible();
}