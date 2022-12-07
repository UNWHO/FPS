#pragma once
#include <d3dx9.h>
#include <unordered_map>
#include <vector>

#include "enum.h"
#include "object.h"
#include "gameManager.h"

class Scene
{
private:
	D3DXMATRIX worldMatrix;
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projectionMatrix;

	std::unordered_map<ObjectIndex, Object*> objectMap;
	std::vector<Object*> objectVector;

	DWORD lightIndex;

	IDirect3DDevice9* device;
	ID3DXFont* font;

	GameManager gameManager;

	D3DXVECTOR3 cameraPosition;
	D3DXVECTOR3 cameraDirection;

	void attachCamera(const Object*);

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

	Object* findObject(ObjectIndex object) { return objectMap[object]; };


	

	// constants
public:
	static const float BALL_RADIUS;
};