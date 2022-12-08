#include "movingBlock.h"
#include "graphic.h"

bool MovingBlock::init(IDirect3DDevice9* device, D3DXVECTOR3 startPosition, D3DXVECTOR3 arrivalPosition, float speed)
{
	this->startPosition = startPosition;
	this->arrivalPosition = arrivalPosition;
	this->speed = speed;


	direction = true;

	setPosition(startPosition);

	D3DXVECTOR3 velocity = arrivalPosition - startPosition;
	distanceSq = D3DXVec3LengthSq(&velocity);

	D3DXVec3Normalize(&velocity, &velocity);
	velocity = velocity * speed;
	setVelocity(velocity);

	size.x = 2.0f;
	size.y = 0.2f;
	size.z = 2.0f;

	if (NULL == device)
		return false;

	setMaterial(Graphic::BLUE, 5.0f);
	setStatic();
	setShape(CUBOID);

	ID3DXMesh* cuboidMesh;
	if (FAILED(D3DXCreateBox(device, size.x, size.y, size.z, &cuboidMesh, NULL)))
		return false;
	setMesh(cuboidMesh);

	return true;

}

void MovingBlock::onBeforeRender()
{
	D3DXVECTOR3 from = direction ? startPosition : arrivalPosition;
	D3DXVECTOR3 to = direction ? arrivalPosition : startPosition;

	D3DXVECTOR3 distance = getPosition() - from;

	if (D3DXVec3LengthSq(&distance) < distanceSq)
		return;

	setPosition(to);
	setVelocity(-getVelocity());
	direction = !direction;
}