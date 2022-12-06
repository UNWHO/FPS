#pragma once
#include "object.h"
#include "sphere.h"
#include "cuboid.h"
#include "line.h"

namespace Physics
{
	const float RESPONSE_OFFSET = 0.0001f;

	bool checkCollision(const Sphere*, const Sphere*);
	bool checkCollision(const Sphere*, const Cuboid*);
	bool checkCollision(const Cuboid*, const Cuboid*);
	bool checkCollision(const Line*, const Sphere*);

	void responseCollision(Sphere*, Sphere*);
	void responseCollision(Sphere*, Cuboid*);
	void responseCollision(Cuboid*, Cuboid*);
	void responseCollision(Line*, Sphere*);
}