#pragma once
#include "object.h"
#include "sphere.h"
#include "cuboid.h"

namespace Physics
{
	const float RESPONSE_OFFSET = 0.0005f;

	bool checkCollision(const Sphere*, const Sphere*);
	bool checkCollision(const Sphere*, const Cuboid*);
	bool checkCollision(const Cuboid*, const Cuboid*);

	void responseCollision(Sphere*, Sphere*);
	void responseCollision(Sphere*, Cuboid*);
	void responseCollision(Cuboid*, Cuboid*);
}