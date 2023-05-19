#include "Shape.h"

Shape::Shape()
{
}

Shape::~Shape()
{
	if(vertices != nullptr)
	delete[] vertices;
}
