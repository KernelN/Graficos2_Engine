#pragma once
#include "Entity/Entity2D/Shape/Shape.h"

class DLLEXPORT Square : public Shape
{
public:
	Square(float vertexPos[8], bool triangleIsStatic);
	~Square();
	void Draw();
private:
	void UpdateVertex(float vertexPos[8]);
};