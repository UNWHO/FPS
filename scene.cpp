#include "scene.h"
#include "object.h"
#include "sphere.h"
#include "cuboid.h"
#include "light.h"
#include "window.h"
#include "graphic.h"
#include "player.h"

#include <iostream>

// initialize constant variable
const float Scene::BALL_RADIUS = 0.1f;

bool Scene::initSpheres(IDirect3DDevice9* device)
{
	Sphere* sphere;

	sphere = new Sphere();
	if (false == sphere->init(device, Graphic::YELLOW, BALL_RADIUS)) return false;
	sphere->setPosition({ 3.3f, BALL_RADIUS, 0.0f });
	sphere->setVelocity({ 0.0f, 0.0f, 0.0f });
	objectMap[YELLOW_BALL] = sphere;

	sphere = new Sphere();
	if (false == sphere->init(device, Graphic::RED, BALL_RADIUS)) return false;
	sphere->setPosition({ -2.7f, BALL_RADIUS + 0.1f, 0.0f });
	sphere->setVelocity({ 0.0f, 0.0f, 0.0f });
	objectMap[RED_BALL_A] = sphere;

	sphere = new Sphere();
	if (false == sphere->init(device, Graphic::RED, BALL_RADIUS)) return false;
	sphere->setPosition({ -2.0f, BALL_RADIUS, 0.0f });
	sphere->setVelocity({ 0.0f, 0.0f, 0.0f });
	objectMap[RED_BALL_B] = sphere;

	return true;
}

bool Scene::initCuboids(IDirect3DDevice9* device)
{
	Cuboid* cuboid;

	// create plane and set the position
	cuboid = new Cuboid();
	if (false == cuboid->init(device, { 9.0f, 0.3f, 6.0f }, Graphic::GREEN)) return false;
	cuboid->setPosition({ 0.0f, -0.18f, 0.0f });
	cuboid->setStatic();
	objectMap[PLANE] = cuboid;

	// create walls and set the position. note that there are four walls
	cuboid = new Cuboid();
	if (false == cuboid->init(device, { 9.0f, 0.3f, 0.12f }, Graphic::DARKRED)) return false;
	cuboid->setPosition({ 0.0f, 0.12f, 3.06f });
	cuboid->setStatic();
	objectMap[WALL_LEFT] = cuboid;

	cuboid = new Cuboid();
	if (false == cuboid->init(device, { 9.0f, 0.3f, 0.12f }, Graphic::DARKRED)) return false;
	cuboid->setPosition({ 0.0f, 0.12f, -3.06f });
	cuboid->setStatic();
	objectMap[WALL_RIGHT] = cuboid;

	cuboid = new Cuboid();
	if (false == cuboid->init(device, { 0.12f, 0.3f, 6.24f }, Graphic::DARKRED)) return false;
	cuboid->setPosition({ 4.56f, 0.12f, 0.0f });
	cuboid->setStatic();
	objectMap[WALL_UP] = cuboid;

	cuboid = new Cuboid();
	if (false == cuboid->init(device, { 0.12f, 0.3f, 6.24f }, Graphic::DARKRED)) return false;
	cuboid->setPosition({ -4.56f, 0.12f, 0.0f });
	cuboid->setStatic();
	objectMap[WALL_DOWN] = cuboid;

	cuboid = new Cuboid();
	if (false == cuboid->init(device, { 0.2f, 0.3f, 0.24f }, Graphic::DARKRED)) return false;
	cuboid->setPosition({ 0.0f, 0.05f, 0.0f });
	cuboid->setStatic();
	cuboid->setVelocity({ 0.1f,0.0f,0.0f });
	objectMap[BLOCK] = cuboid;

	return true;
}

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
	if (false == playerFoot->init(device)) return false;
	objectMap[PLAYER_FOOT] = playerFoot;

	if (false == initSpheres(device)) return false;
	if (false == initCuboids(device)) return false;
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
	cameraPosition = object->getPosition() + D3DXVECTOR3(-0.5f, 0.0f, 0.0f);

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

	//gameManager.updatePlayer(objects[PLAYER], objects[PLAYER_FOOT]);
	
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
			for (iterB++; iterB != objectVector.end(); iterB++)
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
