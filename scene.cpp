#include "scene.h"
#include "object.h"
#include "sphere.h"
#include "cuboid.h"
#include "line.h"
#include "light.h"
#include "window.h"
#include "graphic.h"

#include <iostream>

// initialize constant variable
const float Scene::BALL_RADIUS = 0.21f;

bool Scene::init(IDirect3DDevice9* device, ID3DXFont* font)
{
	this->device = device;
	this->font = font;

	Sphere* sphere;

	sphere = new Sphere();
	if (false == sphere->init(device, Graphic::WHITE, BALL_RADIUS)) return false;
	sphere->setPosition({ -2.7f, BALL_RADIUS, -0.9f });
	sphere->setVelocity({ 0.0f, 0.0f, 0.0f });
	sphere->applyGravity();
	objects[PLAYER] = sphere;

	sphere = new Sphere();
	if (false == sphere->init(device, Graphic::YELLOW, BALL_RADIUS)) return false;
	sphere->setPosition({ 3.3f, BALL_RADIUS, 0.0f });
	sphere->setVelocity({ 0.0f, 0.0f, 0.0f });
	objects[YELLOW_BALL] = sphere;

	sphere = new Sphere();
	if (false == sphere->init(device, Graphic::RED, BALL_RADIUS)) return false;
	sphere->setPosition({ -2.7f, BALL_RADIUS, 0.0f });
	sphere->setVelocity({ 0.0f, 0.0f, 0.0f });
	objects[RED_BALL_A] = sphere;

	sphere = new Sphere();
	if (false == sphere->init(device, Graphic::RED, BALL_RADIUS)) return false;
	sphere->setPosition({ -2.0f, BALL_RADIUS, 0.0f });
	sphere->setVelocity({ 0.0f, 0.0f, 0.0f });
	objects[RED_BALL_B] = sphere;

	Cuboid* cuboid;

	// create plane and set the position
	cuboid = new Cuboid();
	if (false == cuboid->init(device, { 9.0f, 0.03f, 6.0f }, Graphic::GREEN)) return false;
	cuboid->setPosition({ 0.0f, -0.0006f / 5, 0.0f });
	cuboid->setRenderOnly();
	cuboid->setStatic();
	objects[PLANE] = cuboid;

	// create walls and set the position. note that there are four walls
	cuboid = new Cuboid();
	if (false == cuboid->init(device, { 9.0f, 0.3f, 0.12f }, Graphic::DARKRED)) return false;
	cuboid->setPosition({ 0.0f, 0.12f, 3.06f });
	cuboid->setStatic();
	objects[WALL_LEFT] = cuboid;

	cuboid = new Cuboid();
	if (false == cuboid->init(device, { 9.0f, 0.3f, 0.12f }, Graphic::DARKRED)) return false;
	cuboid->setPosition({ 0.0f, 0.12f, -3.06f });
	cuboid->setStatic();
	objects[WALL_RIGHT] = cuboid;

	cuboid = new Cuboid();
	if (false == cuboid->init(device, { 0.12f, 0.3f, 6.24f }, Graphic::DARKRED)) return false;
	cuboid->setPosition({ 4.56f, 0.12f, 0.0f });
	cuboid->setStatic();
	objects[WALL_UP] = cuboid;

	cuboid = new Cuboid();
	if (false == cuboid->init(device, { 0.12f, 0.3f, 6.24f }, Graphic::DARKRED)) return false;
	cuboid->setPosition({ -4.56f, 0.12f, 0.0f });
	cuboid->setStatic();
	objects[WALL_DOWN] = cuboid;

	// create light
	D3DLIGHT9 d3dLight;
	ZeroMemory(&d3dLight, sizeof(d3dLight));
	d3dLight.Type = D3DLIGHT_POINT;
	d3dLight.Diffuse = Graphic::WHITE;
	d3dLight.Specular = Graphic::WHITE * 0.9f;
	d3dLight.Ambient = Graphic::WHITE * 0.9f;
	d3dLight.Position = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
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
	objects[LIGHT] = light;

	// set matrices
	attachCamera(objects[PLAYER]);

	Window& window = Window::getInstance();
	float ratio = (float)window.getWidth() / window.getHeight();

	//D3DXMatrixOrthoLH(&projectionMatrix, 8.0f * ratio, 8.0f, 1.0f, 100.0f);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, 
		(float)window.getWidth() / window.getHeight(), 0.001f, 100.0f);
	device->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_PHONG);

	light->setLight(device, worldMatrix);
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
	for (auto object = objects.begin(); object != objects.end(); object++) {
		//	g_legowall[i].draw(Device, g_mWorld);
		delete object->second;
	}
}

void Scene::update()
{
	Window& window = Window::getInstance();

	// change render mode
	if (window.isKeyPressed(RETURN)) {
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	gameManager.updatePlayer(objects[PLAYER]);
	attachCamera(objects[PLAYER]);
}

void Scene::render(float timeDelta)
{
	if (device)
	{
		device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00afafaf, 1.0f, 0);
		device->BeginScene();

		for (auto object = objects.begin(); object != objects.end(); object++) {
			object->second->update(timeDelta);
		}

		gameManager.checkPlayerJumping(objects[PLAYER]);


		std::unordered_map<ObjectIndex, Object*>::iterator object, target;

		

		for (object = objects.begin(); object != objects.end(); object++) 
		{
			target = object;
			for (target++; target != objects.end(); target++)
			{
				if (object->second->collideWith(target->second))
				{
					object->second->response(target->second);
				}
			}
			object->second->render(device, worldMatrix);
		}	

		device->EndScene();
		device->Present(0, 0, 0, 0);
		device->SetTexture(0, NULL);
	}
}
