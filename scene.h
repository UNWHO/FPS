#pragma once
#include <d3dx9.h>
#include <unordered_map>
#include <vector>

#include "camera.h"
#include "enum.h"
#include "object.h"
#include "gameManager.h"

class Scene
{
private:
	D3DXMATRIX worldMatrix;

	std::unordered_map<ObjectIndex, Object*> objectMap;
	std::vector<Object*> objectVector;

	DWORD lightIndex;

	IDirect3DDevice9* device;
	ID3DXFont* font;

	GameManager gameManager;
	Camera camera;

	bool initLight(IDirect3DDevice9*);

	Scene() :
		lightIndex(NULL)
	{
		D3DXMatrixIdentity(&worldMatrix);
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