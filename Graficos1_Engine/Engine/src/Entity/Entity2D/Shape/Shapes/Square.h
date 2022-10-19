#pragma once
#include "Entity/Entity2D/Shape/Shape.h"

class DLLEXPORT Square : public Shape
{
public:
	Square(float vertexPos[4][2], float vertexCol[4][4], bool squareIsStatic);
	~Square();
	void Draw();
private:
	void UpdateVertex(float vertexPos[4][2], float vertexCol[4][4]);
};