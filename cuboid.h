#pragma once
#include "object.h"

class Cuboid : public Object
{
protected:
	D3DXVECTOR3 size;

public:
	Cuboid()
	{
		setShape(CUBOID);
	}
	bool init(IDirect3DDevice9*, const D3DXVECTOR3&, D3DXCOLOR);
	virtual bool collideWith(const Object*) const;
	virtual void response(Object*);

	const D3DXVECTOR3& getSize() const { return size; };
};