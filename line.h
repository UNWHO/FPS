#pragma once
#include "object.h"

class Line : public Object
{
private:
	float length;
	float width;

public:
	Line()
	{
		setShape(LINE);
	};

	bool init(IDirect3DDevice9*, D3DXCOLOR, float, float);
	virtual bool collideWith(const Object*) const;
	virtual void response(Object*);

	float getLength() const { return length; };
};