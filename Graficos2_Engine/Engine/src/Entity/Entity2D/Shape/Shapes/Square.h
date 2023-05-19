#pragma once
#include "Entity/Entity2D/Shape/Shape.h"

class DLLEXPORT Square : public Shape
{
public:
	Square(float vertexCol[4][4], bool squareIsStatic);
	~Square();
	void Draw();
private:
	void UpdateVertex(float vertexCol[4][4]);
};