#pragma once

#include "Entity/Entity2D/Shape/Shape.h"

class Square : protected Shape
{
public:
	Square(float vertexPos[8], bool triangleIsStatic);
	Square(float vertexPos[8], bool triangleIsStatic, Renderer* renderer);
	~Square();
	void Draw();
private:
	void UpdateVertex(float vertexPos[8]);
};