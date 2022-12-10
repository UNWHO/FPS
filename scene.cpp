#include "scene.h"
#include "object.h"
#include "light.h"
#include "window.h"
#include "graphic.h"
#include "player.h"
#include "movingBlock.h"
#include "staticBlock.h"
#include "weakBlock.h"
#include "doubleJump.h"
#include "directionalBlock.h"
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


	StaticBlock* plane = new StaticBlock();
	if (false == plane->init(device, { 0.0f, -0.1f, 0.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[START_STEP] = plane;

		plane = new StaticBlock();
		if (false == plane->init(device, { 7.0f, 0.3f, -6.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_1_1] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 9.0f, 0.7f, -8.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_1_2] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 11.0f, 0.9f, -10.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_1_3] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 13.0f, 0.7f, -12.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_1_4] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 15.0f, 0.3f, -14.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_1_5] = plane;

	plane = new StaticBlock();
	if (false == plane->init(device, { 20.0f, -0.1f, -20.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[STEP_1] = plane;

		DirectionalBlock* direcionalBlock = new DirectionalBlock();
		if (false == direcionalBlock->init(device, { 26.0f, -0.1f, -26.0f }, { 8.0f, 0.0f, -8.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_1] = direcionalBlock;
		direcionalBlock = new DirectionalBlock();
		if (false == direcionalBlock->init(device, { 26.0f, -0.1f, -29.0f }, { 3.0f, 0.0f, -5.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_2] = direcionalBlock;
		direcionalBlock = new DirectionalBlock();
		if (false == direcionalBlock->init(device, { 29.0f, -0.1f, -26.0f }, { 5.0f, 0.0f, -1.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_2_7] = direcionalBlock;


	plane = new StaticBlock();
	if (false == plane->init(device, { 40.0f, -0.1f, -40.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[STEP_2] = plane;

		plane = new StaticBlock();
		if (false == plane->init(device, { 46.0f, 0.3f, -35.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_3_1] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 48.0f, 0.7f, -35.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_3_2] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 50.0f, 1.1f, -33.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_3_3] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 52.0f, 1.5f, -29.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_3_4] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 52.0f, 1.5f, -31.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_3_5] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 54.0f, 1.9f, -27.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_3_6] = plane;


		WeakBlock* weakBlock = new WeakBlock();
		if (false == weakBlock->init(device, { 46.0f, 0.3f, -37.0f })) return false;
		objectMap[FOR_STEP_3_WEAK_1] = weakBlock;
		weakBlock = new WeakBlock(); 
		if (false == weakBlock->init(device, { 48.0f, 0.7f, -33.0f })) return false;
		objectMap[FOR_STEP_3_WEAK_2] = weakBlock;
		weakBlock = new WeakBlock(); 
		if (false == weakBlock->init(device, { 50.0f, 1.1f, -31.0f })) return false;
		objectMap[FOR_STEP_3_WEAK_3] = weakBlock;
		weakBlock = new WeakBlock(); 
		if (false == weakBlock->init(device, { 54.0f, 1.9f, -29.0f })) return false;
		objectMap[FOR_STEP_3_WEAK_4] = weakBlock;

	plane = new StaticBlock();
	if (false == plane->init(device, { 60.0f, 2.3f, -30.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[STEP_3] = plane;

	//To go to step 4, you should take a ball and jump or take a moving block.
		DoubleJump* doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 60.0f, 2.7f, -30.0f })) return false;
		objectMap[FOR_STEP_4_JUMP_1] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 70.0f, 2.7f, -32.0f })) return false;
		objectMap[FOR_STEP_4_JUMP_2] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 69.0f, 2.7f, -28.0f })) return false;
		objectMap[FOR_STEP_4_JUMP_3] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 71.0f, 2.7f, -28.0f })) return false;
		objectMap[FOR_STEP_4_JUMP_4] = doubleJump;

		weakBlock = new WeakBlock(); 
		if (false == weakBlock->init(device, { 69.0f, 2.3f, -28.0f })) return false;
		objectMap[FOR_STEP_4_WEAK_1] = weakBlock;
		weakBlock = new WeakBlock(); 
		if (false == weakBlock->init(device, { 71.0f, 2.3f, -28.0f })) return false;
		objectMap[FOR_STEP_4_WEAK_1] = weakBlock;
		plane = new StaticBlock();
		if (false == plane->init(device, { 70.0f, 2.3f, -32.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_4_1] = plane;
		MovingBlock* movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 66.0f, 2.3f, -30.0f }, { 74.0f, 3.5f, -30.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_4_MOVE_1] = movingBlock;

	plane = new StaticBlock();
	if (false == plane->init(device, { 80.0f, 2.7f, -30.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[STEP_4] = plane;

		plane = new StaticBlock();
		if (false == plane->init(device, { 85.0f, 3.0f, -24.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_5_1] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 87.0f, 3.4f, -22.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_5_2] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 89.0f, 3.8f, -20.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_5_3] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 91.0f, 4.2f, -18.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_5_4] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 93.0f, 4.5f, -16.0f }, { 4.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_5_5] = plane;

		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 85.0f, 3.4f, -24.0f })) return false;
		objectMap[FOR_STEP_5_JUMP_1] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 91.0f, 4.9f, -16.0f })) return false;
		objectMap[FOR_STEP_5_JUMP_2] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 93.0f, 4.9f, -16.0f })) return false;
		objectMap[FOR_STEP_5_JUMP_3] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 95.0f, 4.9f, -16.0f })) return false;
		objectMap[FOR_STEP_5_JUMP_4] = doubleJump;

	plane = new StaticBlock();
	if (false == plane->init(device, { 90.0f, 5.4f, -10.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[STEP_5] = plane;

		plane = new StaticBlock();
		if (false == plane->init(device, { 80.0f, 5.4f, -10.0f }, { 10.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_6] = plane;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 84.0f, 5.6f, -7.0f }, { 84.0f, 5.6f, -13.0f }, 1.5f)) return false;
		objectMap[FOR_STEP_6_MOVE_1] = movingBlock;
	

		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 78.0f, 5.6f, -13.0f }, { 78.0f, 5.6f, -7.0f }, 1.5f)) return false;
		objectMap[FOR_STEP_6_MOVE_4] = movingBlock;


	plane = new StaticBlock();
	if (false == plane->init(device, { 70.0f, 5.8f, -10.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[STEP_6] = plane;

		

		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 64.0f, 5.6f, -10.0f }, { 64.0f, 6.8f, -10.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_7_MOVE_1] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 62.0f, 7.8f, -10.0f }, { 62.0f, 6.4f, -10.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_7_MOVE_2] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 60.0f, 7.4f, -10.0f }, { 60.0f, 8.8f, -10.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_7_MOVE_3] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 58.0f, 9.8f, -10.0f }, { 58.0f, 8.4f, -10.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_7_MOVE_4] = movingBlock;
		movingBlock = new MovingBlock();
		if (false == movingBlock->init(device, { 56.0f, 9.4f, -10.0f }, { 56.0f, 10.6f, -10.0f }, 0.5f)) return false;
		objectMap[FOR_STEP_7_MOVE_5] = movingBlock;
		

	plane = new StaticBlock();
	if (false == plane->init(device, { 50.0f, 10.4f, -10.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[STEP_7] = plane;

		plane = new StaticBlock();
		if (false == plane->init(device, { 43.5f, 10.0f, -9.0f }, { 3.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_1_1] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 43.5f, 10.0f, -11.0f }, { 3.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_1_2] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 44.5f, 10.0f, -10.0f }, { 1.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_1_3] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 42.5f, 10.0f, -10.0f }, { 1.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_1_4] = plane;

		plane = new StaticBlock();
		if (false == plane->init(device, { 43.5f, 9.0f, -9.0f }, { 3.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_2_1] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 43.5f, 9.0f, -11.0f }, { 3.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_2_2] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 44.5f, 9.0f, -10.0f }, { 1.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_2_3] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 42.5f, 9.0f, -10.0f }, { 1.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_2_4] = plane;

		plane = new StaticBlock();
		if (false == plane->init(device, { 43.5f, 8.0f, -9.0f }, { 3.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_3_1] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 43.5f, 8.0f, -11.0f }, { 3.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_3_2] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 44.5f, 8.0f, -10.0f }, { 1.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_3_3] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 42.5f, 8.0f, -10.0f }, { 1.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_3_4] = plane;

		plane = new StaticBlock();
		if (false == plane->init(device, { 43.5f, 7.0f, -9.0f }, { 3.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_4_1] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 43.5f, 7.0f, -11.0f }, { 3.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_4_2] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 44.5f, 7.0f, -10.0f }, { 1.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_4_3] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 42.5f, 7.0f, -10.0f }, { 1.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_4_4] = plane;

		plane = new StaticBlock();
		if (false == plane->init(device, { 43.5f, 6.0f, -9.0f }, { 3.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_5_1] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 43.5f, 6.0f, -11.0f }, { 3.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_5_2] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 44.5f, 6.0f, -10.0f }, { 1.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_5_3] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 42.5f, 6.0f, -10.0f }, { 1.0f, 0.2f, 1.0f })) return false;
		objectMap[FOR_STEP_8_5_4] = plane;

		
	plane = new StaticBlock();
	if (false == plane->init(device, { 40.0f, 5.0f, -10.0f }, { 10.0f, 0.2f, 10.0f })) return false;
	objectMap[STEP_8] = plane;

		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 36.0f, 5.4f, -10.0f })) return false;
		objectMap[FOR_STEP_9_JUMP_0] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 34.0f, 5.9f, -10.0f })) return false;
		objectMap[FOR_STEP_9_JUMP_1] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 31.0f, 6.4f, -9.0f })) return false;
		objectMap[FOR_STEP_9_JUMP_2] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 28.0f, 6.9f, -8.0f })) return false;
		objectMap[FOR_STEP_9_JUMP_3] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 25.0f, 7.4f, -7.0f })) return false;
		objectMap[FOR_STEP_9_JUMP_4] = doubleJump;

		
		plane = new StaticBlock();
		if (false == plane->init(device, { 34.0f, 5.5f, -10.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_9_1] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 31.0f, 6.0f, -9.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_9_2] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 28.0f, 6.5f, -8.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_9_3] = plane;
		plane = new StaticBlock();
		if (false == plane->init(device, { 25.0f, 7.0f, -7.0f }, { 2.0f, 0.2f, 2.0f })) return false;
		objectMap[FOR_STEP_9_4] = plane;
		

		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 24.0f, 7.7f, 0.0f })) return false;
		objectMap[FOR_STEP_9_JUMP_5] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 20.0f, 7.7f, -4.0f })) return false;
		objectMap[FOR_STEP_9_JUMP_6] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 22.0f, 8.2f, 0.0f })) return false;
		objectMap[FOR_STEP_9_JUMP_7] = doubleJump;
		doubleJump = new DoubleJump();
		if (false == doubleJump->init(device, { 20.0f, 8.2f, -2.0f })) return false;
		objectMap[FOR_STEP_9_JUMP_8] = doubleJump;


	plane = new StaticBlock();
	if (false == plane->init(device, { 20.0f, 7.5f, 0.0f }, { 10.0f, 1.6f, 10.0f })) return false;
	objectMap[STEP_9_1] = plane;
	plane = new StaticBlock();
	if (false == plane->init(device, { 20.0f, 8.0f, 0.0f }, { 6.0f, 1.6f, 6.0f })) return false;
	objectMap[STEP_9_2] = plane;
	plane = new StaticBlock();
	if (false == plane->init(device, { 20.0f, 8.5f, 0.0f }, { 2.0f, 1.6f, 2.0f })) return false;
	objectMap[STEP_9_3] = plane;

	if (false == initLight(device)) return false;

	for (auto iter = objectMap.begin(); iter != objectMap.end(); iter++) {
		objectVector.push_back(iter->second);
	}

	camera.init(device);
	camera.attach(player);


	Window& window = Window::getInstance();
	float ratio = (float)window.getWidth() / window.getHeight();

	D3DXMATRIX projectionMatrix;
	//D3DXMatrixOrthoLH(&projectionMatrix, 8.0f * ratio, 8.0f, 1.0f, 100.0f);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, 
		(float)window.getWidth() / window.getHeight(), 0.001f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_PHONG);

	return true;
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

			object->onBeforeUpdate(timeDelta);
			object->update(timeDelta);
			object->onUpdate(timeDelta);
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
					if (!((*iterA)->isDetectOnly()) && !((*iterB)->isDetectOnly()))
					{
						(*iterA)->response(*iterB);
					}


					(*iterA)->onCollide(*iterB);
					(*iterB)->onCollide(*iterA);
				}
			}
		}	

		camera.update();

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
