#include "goal.h"
#include "graphic.h"
#include "scene.h"
#include "gameManager.h"

bool Goal::init(IDirect3DDevice9* device, D3DXVECTOR3 position)
{
	if (NULL == device)
		return false;

	radius = 0.2f;
	setShape(SPHERE);
	setMaterial(Graphic::GREEN, 5.0f);

	ID3DXMesh* sphereMesh;
	if (FAILED(D3DXCreateSphere(device, radius, 50, 50, &sphereMesh, NULL)))
		return false;
	setMesh(sphereMesh);

	setPosition(position);
	setVelocity({ 0.0f, 0.0f, 0.0f });

	setDetectOnly();

	return true;
}

void Goal::onCollide(Object* target)
{
	Scene& scene = Scene::getInstance();
	GameManager& gameManager = scene.getGameManager();

	gameManager.gameOver();


	setInvisible();
	setRenderOnly();
}

