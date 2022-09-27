#pragma once

#include "Entity/Entity2D/Shape/Shape.h"

class Triangle : protected Shape
{
public:
	Triangle(float vertexPos[6], bool triangleIsStatic);
	~Triangle();
	void Draw();
private:
	void UpdateVertex(float vertexPos[6]);
};