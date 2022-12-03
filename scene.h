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
	void render(float);


	

	// constants
public:
	static const float BALL_RADIUS;
};