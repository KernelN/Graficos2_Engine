#pragma once

#include "Entity/Entity2D/Shape/Shape.h"

class Triangle : protected Shape
{
public:
	Triangle(float vertexPos[6], bool triangleIsStatic);
	Triangle(float vertexPos[6], bool triangleIsStatic, Renderer* renderer);
	~Triangle();
	void Draw();
private:
	float vertexPos[6];
	void UpdateVertex(float vertexPos[6]);
};