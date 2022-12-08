#include "scene.h"
#include "object.h"
#include "light.h"
#include "window.h"
#include "graphic.h"
#include "player.h"
#include "movingBlock.h"
#include "staticBlock.h"
#include "weakBlock.h"
#include <iostream>

// initialize constant variable
const float Scene::BALL_RADIUS = 0.1f;

bool Scene::initLight(IDirect3DDevice9* device)
{
	// create light
	D3DLIGHT9 d3dLight;
	ZeroMemory(&d3dLight, sizeof(d3dLight));
	d3dLight.Type = D3DLIGHT_DIRECTIONAL;
	d3dLight.Diffuse = Graphic::WHITE * 0.3f;
	d3dLight.Specular = Graphic::WHITE * 0.5f;
	d3dLight.Ambient = Graphic::WHITE * 0.3f;
	d3dLight.Direction = D3DXVECTOR3(-1.0f, -1.0f, -1.0f);
	d3dLight.Range = 100.0f;
	d3dLight.Attenuation0 = 0.0f;
	d3dLight.Attenuation1 = 0.9f;
	d3dLight.Attenuation2 = 0.0f;

	Light* light = new Light();
	if (false == light->init(device, d3dLight, 0.1f, lightIndex))
		return false;
	light->setInvisible();
	light->setRenderOnly();
	light->setStatic();
	objectMap[LIGHT] = light;

	light->setLight(device, worldMatrix);

	return true;
}

bool Scene::init(IDirect3DDevice9* device, ID3DXFont* font)
{
	this->device = device;
	this->font = font;

	gameManager.init(font);

	
	Player* player = new Player();
	if (false == player->init(device)) return false;
	objectMap[PLAYER] = player;
	
	PlayerFoot* playerFoot = new PlayerFoot();
	if (false == playerFoot->init(device, player)) return false;
	objectMap[PLAYER_FOOT] = playerFoot;


	WeakBlock* weakBlock = new WeakBlock(); //fake_block
	if (false == weakBlock->init(device, { -3.0f, 0.16f, 1.0f })) return false;
	objectMap[WEAK_TEST] = weakBlock;


	MovingBlock* movingBlock = new MovingBlock();
	if (false == movingBlock->init(device, { 1.0f, 0.15f, 1.0f }, { -1.0f, 0.15f, 1.0f }, 0.25f)) return false;
	objectMap[MOVING_TEST] = movingBlock;

	StaticBlock* plane = new StaticBlock();
	if (false == plane->init(device, { 0.0f, -0.1f, 0.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[START_STEP] = plane;
	
	

		plane = new StaticBlock();
		if (false == plane->init(device, { 7.0f, -0.1f, -6.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_1_1] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 9.0f, -0.1f, -8.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_1_2] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 11.0f, -0.1f, -10.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_1_3] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 13.0f, -0.1f, -12.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_1_4] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 15.0f, -0.1f, -14.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_1_5] = plane;



	plane = new StaticBlock();
	if (false == plane->init(device, { 20.0f, -0.1f, -20.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[STEP_1] = plane;

		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 26.0f, 0.15f, -26.0f }, { 26.0f, 0.15f, -34.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_1] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 26.0f, 0.15f, -29.0f }, { 26.0f, 0.15f, -37.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_2] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 26.0f, 0.15f, -32.0f }, { 26.0f, 0.15f, -40.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_3] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 28.0f, 0.15f, -27.0f }, { 28.0f, 0.15f, -35.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_4] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 28.0f, 0.15f, -30.0f }, { 28.0f, 0.15f, -38.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_5] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 28.0f, 0.15f, -33.0f }, { 28.0f, 0.15f, -41.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_6] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 30.0f, 0.15f, -26.0f }, { 30.0f, 0.15f, -34.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_7] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 30.0f, 0.15f, -29.0f }, { 30.0f, 0.15f, -37.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_8] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 30.0f, 0.15f, -32.0f }, { 30.0f, 0.15f, -40.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_9] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 32.0f, 0.15f, -27.0f }, { 32.0f, 0.15f, -35.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_10] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 32.0f, 0.15f, -30.0f }, { 32.0f, 0.15f, -38.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_11] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 32.0f, 0.15f, -33.0f }, { 32.0f, 0.15f, -41.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_12] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 34.0f, 0.15f, -26.0f }, { 34.0f, 0.15f, -34.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_13] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 34.0f, 0.15f, -29.0f }, { 34.0f, 0.15f, -37.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_14] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 34.0f, 0.15f, -32.0f }, { 34.0f, 0.15f, -40.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_15] = movingBlock;
		

	plane = new StaticBlock();
	if (false == plane->init(device, { 40.0f, -0.1f, -40.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[STEP_2] = plane;
	plane = new StaticBlock();
		if (false == plane->init(device, { 46.0f, 0.7f, -35.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_3_1] = plane;
		if (false == plane->init(device, { 48.0f, 1.4f, -35.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_3_2] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 50.0f, 2.1f, -33.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_3_3] = plane;
		if (false == plane->init(device, { 52.0f, 2.8f, -29.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_3_4] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 52.0f, 2.8f, -31.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_3_5] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 54.0f, 3.5f, -27.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_3_6] = plane;

		weakBlock = new WeakBlock(); //fake_block
		if (false == weakBlock->init(device, { 46.0f, 0.7f, -37.0f })) return false;
		objectMap[FOR_STEP_3_WEAK_1] = weakBlock;
		weakBlock = new WeakBlock(); //fake_block
		if (false == weakBlock->init(device, { 48.0f, 1.4f, -33.0f })) return false;
		objectMap[FOR_STEP_3_WEAK_2] = weakBlock;
		 weakBlock = new WeakBlock(); //fake_block
		if (false == weakBlock->init(device, { 50.0f, 2.1f, -31.0f })) return false;
		objectMap[FOR_STEP_3_WEAK_3] = weakBlock;
		 weakBlock = new WeakBlock(); //fake_block
		if (false == weakBlock->init(device, { 54.0f, 3.5f, -29.0f })) return false;
		objectMap[FOR_STEP_3_WEAK_4] = weakBlock;

	plane = new StaticBlock();
	if (false == plane->init(device, { 60.0f, 3.5f, -30.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[STEP_3] = plane;

		weakBlock = new WeakBlock(); //fake_block
		if (false == weakBlock->init(device, { 69.0f, 3.5f, -28.0f })) return false;
		objectMap[FOR_STEP_4_WEAK_1] = weakBlock;
		weakBlock = new WeakBlock(); //fake_block
		if (false == weakBlock->init(device, { 71.0f, 3.5f, -28.0f })) return false;
		objectMap[FOR_STEP_4_WEAK_1] = weakBlock;
		plane = new StaticBlock();
		if (false == plane->init(device, { 70.0f, 3.5f, -32.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_4_1] = plane;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 66.0f, 3.5f, -30.0f }, { 74.0f, 3.5f, -30.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_4_MOVE_1] = movingBlock;
	
		plane = new StaticBlock();
	if (false == plane->init(device, { 80.0f, 3.5f, -30.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[STEP_4] = plane;
	

	if (false == initLight(device)) return false;

	for (auto iter = objectMap.begin(); iter != objectMap.end(); iter++) {
		objectVector.push_back(iter->second);
	}

	attachCamera(objectMap[PLAYER]);

	Window& window = Window::getInstance();
	float ratio = (float)window.getWidth() / window.getHeight();

	//D3DXMatrixOrthoLH(&projectionMatrix, 8.0f * ratio, 8.0f, 1.0f, 100.0f);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, 
		(float)window.getWidth() / window.getHeight(), 0.001f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);



	
	return true;
}

void Scene::attachCamera(const Object* object)
{
	D3DXVECTOR3 objectAngle = object->getAngle();
	cameraDirection = (cameraDirection + objectAngle) / 2;
	cameraPosition = object->getPosition();

	D3DXMATRIX rotateX, rotateY, rotateZ, rotate;
	D3DXMatrixRotationX(&rotateX, cameraDirection.x);
	D3DXMatrixRotationY(&rotateY, cameraDirection.y);
	D3DXMatrixRotationZ(&rotateZ, cameraDirection.z);
	rotate = rotateZ * rotateY * rotateX;

	D3DXVECTOR4 cameraTargetDir;
	D3DXVec3Transform(&cameraTargetDir, &D3DXVECTOR3(1.0f, 0.0f, 0.0f), &rotate);
	D3DXVECTOR3 cameraTargetPosition = cameraPosition + D3DXVECTOR3(cameraTargetDir);

	D3DXVECTOR4 cameraUp;
	D3DXVec3Transform(&cameraUp, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), &rotate);


	
	D3DXMatrixLookAtLH(&viewMatrix, &cameraPosition, &cameraTargetPosition, &D3DXVECTOR3(0, 1, 0));
	device->SetTransform(D3DTS_VIEW, &viewMatrix);
}

void Scene::destory()
{
	for (auto object = objectVector.begin(); object != objectVector.end(); object++) {
		//	g_legowall[i].draw(Device, g_mWorld);
		delete (*object);
	}
}

void Scene::update()
{
	Window& window = Window::getInstance();

	// change render mode
	if (window.isKeyPressed(RETURN)) {
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}	
}

void Scene::render(unsigned long timeDelta)
{
	if (device)
	{
		device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00afafaf, 1.0f, 0);
		device->BeginScene();

		// update objects
		for (auto iter = objectVector.begin(); iter != objectVector.end(); iter++) {
			Object* object = *iter;

			object->onBeforeUpdate();
			object->update(timeDelta);
			object->onUpdate();
		}

		// collision detection / response
		std::vector<Object*>::iterator iterA, iterB;	
		for (iterA = objectVector.begin(); iterA != objectVector.end(); iterA++)
		{
			iterB = iterA;
			for (++iterB; iterB != objectVector.end(); iterB++)
			{
				if ((*iterA)->collideWith(*iterB))
				{
					(*iterA)->onCollide();
					(*iterB)->onCollide();

					if ((*iterA)->isDetectOnly() || (*iterB)->isDetectOnly()) continue;

					(*iterA)->response(*iterB);
				}
			}
		}	

		attachCamera(objectMap[PLAYER]);

		// render
		for (auto iter = objectVector.begin(); iter != objectVector.end(); iter++) {
			(*iter)->onBeforeRender();
			(*iter)->render(device, worldMatrix);
		}

		
		gameManager.printFPS(timeDelta);
		gameManager.printPlayerPosition(objectMap[PLAYER]);

		device->EndScene();
		device->Present(0, 0, 0, 0);
		device->SetTexture(0, NULL);
	}
}
