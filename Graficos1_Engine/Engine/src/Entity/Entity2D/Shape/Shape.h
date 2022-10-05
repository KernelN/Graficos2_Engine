#pragma once

#include "Entity/Entity2D/Entity2D.h"

class DLLEXPORT Shape : public Entity2D
{
public:
	Shape();
	~Shape();
protected:
	Vertex* vertices;
	unsigned int* indices;
};