#pragma once
#include <d3dx9.h>
#include <unordered_map>

#include "enum.h"
#include "object.h"
#include "gameManager.h"

class Scene
{
private:
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;

	std::unordered_map<ObjectIndex, Object*> objects;
	DWORD lightIndex;

	IDirect3DDevice9* device;
	ID3DXFont* font;

	GameManager gameManager;

	D3DXVECTOR3 cameraPosition;
	D3DXVECTOR3 cameraDirection;

	void attachCamera(const Object*);


	bool Scene::makingCuboids(IDirect3DDevice9* device, float x_size, float z_size, float y_size, float x_pos, float z_pos, float y_pos, D3DXCOLOR color, enum ObjectIndex numberIndex);
	bool Scene::makingSpheres(IDirect3DDevice9* device, float x_pos, float z_pos, float y_pos, float x_vel, float z_vel, float y_vel, int r, D3DXCOLOR color, enum ObjectIndex numberIndex);

	bool initFirstFloor(IDirect3DDevice9*);
	bool initSecondFloor(IDirect3DDevice9*);
	bool initThirdFloor(IDirect3DDevice9*);
	bool initFourthFloor(IDirect3DDevice9*);
	bool initFifthFloor(IDirect3DDevice9*);
	bool initSixthFloor(IDirect3DDevice9*);
	bool initSeventhFloor(IDirect3DDevice9*);
	bool initEighthFloor(IDirect3DDevice9*);
	bool initNinethFloor(IDirect3DDevice9*);
	bool initTenthFloor(IDirect3DDevice9*);
	bool initEleventhFloor(IDirect3DDevice9*);


	bool initSpheres(IDirect3DDevice9*);
	bool initCuboids(IDirect3DDevice9*);
	bool initLight(IDirect3DDevice9*);

	Scene() :
		lightIndex(NULL)
	{
		D3DXMatrixIdentity(&worldMatrix);
		D3DXMatrixIdentity(&viewMatrix);
		D3DXMatrixIdentity(&projectionMatrix);
	}
	Scene(const Scene& ref);
	Scene& operator=(const Scene& ref) {}
	~Scene() {}

public:
	static Scene& getInstance()
	{
		static Scene scene;
		return scene;
	}
	 
	bool init(IDirect3DDevice9*, ID3DXFont*);
	void destory();
	
	void update();
	void render(unsigned long);


	

	// constants
public:
	static const float BALL_RADIUS;
};