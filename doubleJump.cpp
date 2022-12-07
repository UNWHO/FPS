#include "doubleJump.h"
#include "graphic.h"
#include "scene.h"
#include "player.h"

bool DoubleJump::init(IDirect3DDevice9* device, D3DXVECTOR3 position)
{
	if (NULL == device)
		return false;

	radius = 0.1f;
	setShape(SPHERE);
	setMaterial(Graphic::MAGENTA, 5.0f);

	ID3DXMesh* sphereMesh;
	if (FAILED(D3DXCreateSphere(device, radius, 50, 50, &sphereMesh, NULL)))
		return false;
	setMesh(sphereMesh);

	setPosition(position);
	setVelocity({ 0.0f, 0.0f, 0.0f });
	
	setDetectOnly();

	return true;
}

void DoubleJump::onCollide(Object* target)
{
	Scene& scene = Scene::getInstance();
	Player* player = dynamic_cast<Player*>(scene.findObject(PLAYER));
	player->getDoubleJumpItem();


	setInvisible();
	setRenderOnly();
}

