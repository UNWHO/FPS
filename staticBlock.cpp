#include "staticBlock.h"
#include "graphic.h"

bool StaticBlock::init(IDirect3DDevice9* device, D3DXVECTOR3 position, D3DXVECTOR3 size = {3.2f, 0.2f, 1.6f})
{
	this->size = size;

	setPosition(position);
	setStatic();

	if (NULL == device)
		return false;

	setMaterial(Graphic::GRAY, 5.0f);
	setStatic();

	ID3DXMesh* cuboidMesh;
	if (FAILED(D3DXCreateBox(device, size.x, size.y, size.z, &cuboidMesh, NULL)))
		return false;
	setMesh(cuboidMesh);

	return true;
}