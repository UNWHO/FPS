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
const float Scene::BALL_RADIUS = 0.1f;

bool Scene::initSpheres(IDirect3DDevice9* device)
{
    Sphere* sphere;

    sphere = new Sphere();
    if (false == sphere->init(device, Graphic::WHITE, BALL_RADIUS)) return false;
    sphere->setPosition({ -2.7f, BALL_RADIUS, -0.9f });
    sphere->setVelocity({ 0.0f, 0.0f, 0.0f });
    sphere->applyGravity();
    objects[PLAYER] = sphere;

    return true;
}

//직육면체랑 구 만드는 함수

bool Scene::makingCuboids(IDirect3DDevice9* device, float x_size, float z_size, float y_size, float x_pos, float z_pos, float y_pos, D3DXCOLOR color, enum ObjectIndex numberIndex) {

    Cuboid* cuboid;

    cuboid = new Cuboid();
    if (false == cuboid->init(device, { x_size, z_size, y_size }, color)) return false;
    cuboid->setPosition({ x_pos, z_pos, y_pos });
    cuboid->setRenderOnly();
    cuboid->setStatic();
    objects[numberIndex] = cuboid;

    return true;

}

bool Scene::makingSpheres(IDirect3DDevice9* device, float x_pos, float z_pos, float y_pos, float x_vel, float z_vel, float y_vel, int r, D3DXCOLOR color, enum ObjectIndex numberIndex)
{
    Sphere* sphere;

    sphere = new Sphere();
    if (false == sphere->init(device, color, r * BALL_RADIUS)) return false;
    sphere->setPosition({ x_pos, z_pos, y_pos });
    sphere->setVelocity({ x_vel, z_vel, y_vel });
    sphere->applyGravity();
    objects[numberIndex] = sphere;

    return true;
}

//1층
bool Scene::initFirstFloor(IDirect3DDevice9* device) {

    makingCuboids(device, 1.0f, 0.2f, 6.4f, 3.0f, 0.6f, 6.5f, Graphic::BLACK, BLOCK_A_1F);
    makingCuboids(device, 1.0f, 0.2f, 6.4f, 6.5f, 0.6f, 6.5f, Graphic::BLACK, BLOCK_C_1F);
    makingCuboids(device, 1.0f, 0.2f, 6.4f, 10.0f, 0.6f, 6.5f, Graphic::BLACK, BLOCK_E_1F);

    makingSpheres(device, 6.5f, 15.5f, 0.6f, 0.0f, 0.0f, 0.0f, 1, Graphic::WHITE, PLAYER);

    return true;
}

//2층
bool Scene::initSecondFloor(IDirect3DDevice9* device) {

    makingCuboids(device, 1.0f, 0.2f, 6.4f, 4.75f, 1.3f, 6.5f, Graphic::WHITE, BLOCK_B_2F);
    makingCuboids(device, 1.0f, 0.2f, 6.4f, 8.25f, 1.3f, 6.5f, Graphic::WHITE, BLOCK_D_2F);

    return true;
}

//3층
bool Scene::initThirdFloor(IDirect3DDevice9* device) {

    makingCuboids(device, 1.6f, 0.2f, 1.0f, 3.0f, 2.0f, 5.7f, Graphic::BLACK, BLOCK_A2_3F);
    makingCuboids(device, 1.6f, 0.2f, 1.0f, 3.0f, 2.0f, 8.9f, Graphic::BLACK, BLOCK_A4_3F);
    makingCuboids(device, 1.6f, 0.2f, 1.0f, 6.5f, 2.0f, 4.1f, Graphic::BLACK, BLOCK_C1_3F);
    makingCuboids(device, 1.6f, 0.2f, 1.0f, 6.5f, 2.0f, 7.3f, Graphic::BLACK, BLOCK_C3_3F);
    makingCuboids(device, 1.6f, 0.2f, 1.0f, 10.0f, 2.0f, 5.7f, Graphic::BLACK, BLOCK_E2_3F);
    makingCuboids(device, 1.6f, 0.2f, 1.0f, 10.0f, 2.0f, 8.9f, Graphic::BLACK, BLOCK_E4_3F);

    return true;
}

//4층
bool Scene::initFourthFloor(IDirect3DDevice9* device) {

    makingCuboids(device, 1.0f, 0.2f, 1.6f, 4.75f, 2.7f, 5.7f, Graphic::WHITE, BLOCK_B2_4F);
    makingCuboids(device, 1.0f, 0.2f, 1.6f, 4.75f, 2.7f, 8.9f, Graphic::WHITE, BLOCK_B4_4F);
    makingCuboids(device, 1.0f, 0.2f, 1.6f, 8.25f, 2.7f, 4.1f, Graphic::WHITE, BLOCK_D1_4F);
    makingCuboids(device, 1.0f, 0.2f, 1.6f, 8.25f, 2.7f, 7.3f, Graphic::WHITE, BLOCK_D3_4F);

    return true;
}

//5층
bool Scene::initFifthFloor(IDirect3DDevice9* device) {

    makingCuboids(device, 1.6f, 0.2f, 1.0f, 3.0f, 3.4f, 5.7f, Graphic::BLACK, BLOCK_A2_5F);
    makingCuboids(device, 1.6f, 0.2f, 1.0f, 6.5f, 3.4f, 7.3f, Graphic::BLACK, BLOCK_C3_5F);

    return true;
}


//6층
bool Scene::initSixthFloor(IDirect3DDevice9* device) {

    makingCuboids(device, 1.0f, 0.2f, 1.6f, 4.75f, 4.1f, 5.7f, Graphic::WHITE, BLOCK_B2_6F);
    makingCuboids(device, 1.0f, 0.2f, 1.6f, 8.25f, 4.1f, 7.3f, Graphic::WHITE, BLOCK_D3_6F);

    return true;
}

//7층
bool Scene::initSeventhFloor(IDirect3DDevice9* device) {

    makingCuboids(device, 1.6f, 0.2f, 1.0f, 6.5f, 4.8f, 6.5f, Graphic::BLACK, BLOCK_CENTER_7F);

    return true;
}

//8층
bool Scene::initEighthFloor(IDirect3DDevice9* device) {

    makingCuboids(device, 1.6f, 0.2f, 1.0f, 6.5f, 5.5f, 6.5f, Graphic::BLACK, BLOCK_CENTER_8F);

    return true;
}


//9층
bool Scene::initNinethFloor(IDirect3DDevice9* device) {

    makingCuboids(device, 1.6f, 0.2f, 1.0f, 3.0f, 6.2f, 5.7f, Graphic::BLACK, BLOCK_A2_9F);
    makingCuboids(device, 1.6f, 0.2f, 1.0f, 6.5f, 6.2f, 7.3f, Graphic::BLACK, BLOCK_C3_9F);

    return true;
}

//10층
bool Scene::initTenthFloor(IDirect3DDevice9* device) {

    makingCuboids(device, 1.0f, 0.2f, 1.6f, 4.75f, 6.9f, 5.7f, Graphic::WHITE, BLOCK_B2_10F);
    makingCuboids(device, 1.0f, 0.2f, 1.6f, 8.25f, 6.9f, 7.3f, Graphic::WHITE, BLOCK_D3_10F);

    return true;
}

//11층
bool Scene::initEleventhFloor(IDirect3DDevice9* device) {

    makingCuboids(device, 1.6f, 0.2f, 1.0f, 6.5f, 7.6f, 7.6f, Graphic::BLACK, BLOCK_CENTER_11F);

    return true;

}



bool Scene::initCuboids(IDirect3DDevice9* device)
{
    Cuboid* cuboid;

    // create plane and set the position
    cuboid = new Cuboid();
    if (false == cuboid->init(device, { 9.0f, 0.03f, 6.0f }, Graphic::WHITE)) return false;
    cuboid->setPosition({ 0.0f, -0.0006f / 5, 0.0f });
    cuboid->setRenderOnly();
    cuboid->setStatic();
    objects[PLANE] = cuboid;
}


bool Scene::initLight(IDirect3DDevice9* device)
{
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

    light->setLight(device, worldMatrix);

    return true;
}

bool Scene::init(IDirect3DDevice9* device, ID3DXFont* font)
{
    this->device = device;
    this->font = font;

    if (false == initSpheres(device)) return false;
    if (false == initCuboids(device)) return false;
    if (false == initLight(device)) return false;
    if (false == initFirstFloor(device)) return false;
    if (false == initSecondFloor(device)) return false;
    if (false == initThirdFloor(device)) return false;
    if (false == initFourthFloor(device)) return false;
    if (false == initFifthFloor(device)) return false;
    if (false == initSixthFloor(device)) return false;
    if (false == initSeventhFloor(device)) return false;
    if (false == initEighthFloor(device)) return false;
    if (false == initNinethFloor(device)) return false;
    if (false == initTenthFloor(device)) return false;
    if (false == initEleventhFloor(device)) return false;

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
        //   g_legowall[i].draw(Device, g_mWorld);
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