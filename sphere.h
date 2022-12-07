#pragma once
#include "object.h"


class Sphere : public Object
{
protected:
	float radius;

public:
	bool init(IDirect3DDevice9*, D3DXCOLOR, float radius);
	virtual bool collideWith(const Object*) const;
	virtual void response(Object*);

	const float getRadius() const { return radius; };
};