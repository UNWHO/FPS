#include "directionalBlock.h"
#include "graphic.h"

bool DirectionalBlock::init(IDirect3DDevice9* device, D3DXVECTOR3 startPosition, D3DXVECTOR3 direction, float speed)
{
	this->startPosition = startPosition;
	this->speed = speed;


	setPosition(startPosition);

	D3DXVECTOR3 velocity = direction;
	distanceSq = D3DXVec3LengthSq(&velocity);

	D3DXVec3Normalize(&velocity, &velocity);
	velocity = velocity * speed;
	setVelocity(velocity);

	size.x = 2.0f;
	size.y = 0.2f;
	size.z = 2.0f;

	if (NULL == device)
		return false;

	setMaterial(Graphic::RED, 5.0f);
	setStatic();
	setShape(CUBOID);

	ID3DXMesh* cuboidMesh;
	if (FAILED(D3DXCreateBox(device, size.x, size.y, size.z, &cuboidMesh, NULL)))
		return false;
	setMesh(cuboidMesh);

	return true;

}

void DirectionalBlock::onBeforeRender()
{
	D3DXVECTOR3 distance = getPosition() - startPosition;

	if (D3DXVec3LengthSq(&distance) < distanceSq)
		return;

	setPosition(startPosition);
}