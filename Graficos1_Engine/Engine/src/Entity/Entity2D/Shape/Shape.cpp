#include "Shape.h"

Shape::Shape()
{
}

Shape::Shape(Renderer* renderer) : Entity2D(renderer)
{
}

Shape::~Shape()
{
	if(vertices != nullptr)
	delete[] vertices;
}
