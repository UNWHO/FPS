#pragma once
#include <d3dx9.h>

enum Shape
{
	SPHERE,
	CUBOID,
	LINE,
	NONE
};


class Object
{
private:
	// about physics
	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;
	D3DXVECTOR3 angle;

	bool renderOnly;	// do nothing about phiysics(collision detect, collistion response)

	bool detectOnly;	// object responsed to collision only if it has volume
	bool staticFlag;	// when collide to other objects, speed changed only if it is non-static object
	
	bool gravity;		// object falls only if its gravity flag turned true
	Shape shape;

	void updateLocalMatrix();

	// about rendering
	D3DXMATRIX localMatrix;
	D3DMATERIAL9 material;
	ID3DXMesh* mesh;
	bool visible;		// object rendered only if it is visible

public:
	Object():
		position({0, 0, 0}),
		velocity({0, 0, 0}),
		angle({0, 0, 0}),
		staticFlag(false),
		renderOnly(false),
		shape(NONE),
		mesh(NULL),
		visible(true),
		gravity(false),
		detectOnly(false)
	{
		D3DXMatrixIdentity(&localMatrix);
		ZeroMemory(&material, sizeof(material));
	};
	~Object()
	{
		if (mesh != NULL) {
			mesh->Release();
			mesh = NULL;
		}
	};

	virtual bool collideWith(const Object*) const = 0;
	virtual void response(Object*) = 0;

	void update(unsigned long);
	void render(IDirect3DDevice9*, const D3DXMATRIX&);

	virtual void onBeforeUpdate(unsigned long) {};
	virtual void onUpdate(unsigned long) {};
	virtual void onCollide(Object*) {};
	virtual void onBeforeRender() {};
	

	const D3DXVECTOR3& getPosition() const { return position; };
	void setPosition(const D3DXVECTOR3&);
	
	const D3DXVECTOR3& getVelocity() const { return velocity; };
	void setVelocity(const D3DXVECTOR3& velocity) 
	{
		this->velocity.x = velocity.x;
		this->velocity.y = velocity.y;
		this->velocity.z = velocity.z;
	};

	const D3DXMATRIX& getLocalMatrix() const { return localMatrix; };

	virtual void setMaterial(D3DXCOLOR, float);

	void setMesh(ID3DXMesh* mesh) { this->mesh = mesh; };

	void setShape(Shape shape) { this->shape = shape; };
	const Shape getShape() const { return shape; };

	bool isStatic() const { return staticFlag; };
	void setStatic() { staticFlag = true; };

	bool isRenderOnly() const { return renderOnly; };
	void setRenderOnly() { renderOnly = true; }
	void clearRenderOnly() { renderOnly = false; };

	void setVisible() { visible = true; };
	void setInvisible() { visible = false; };

	bool isDetectOnly() const { return detectOnly; };
	void setDetectOnly() { detectOnly = true; };

	float getAngleY() const { return angle.y; };
	void rotateY(float);

	const D3DXVECTOR3& getAngle() const { return angle; };
	void rotate(const D3DXVECTOR3&);

	void applyGravity() { gravity = true; };
 	void cancelGravity() { gravity = false; };
};


