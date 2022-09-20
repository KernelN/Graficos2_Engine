#pragma once

#include "Entity/Entity2D/Entity2D.h"

class Shape : protected Entity2D
{
public:
	Shape();
	Shape(Renderer* renderer);
	~Shape();
protected:
	Vertex* vertices;
	unsigned int* indices;
};