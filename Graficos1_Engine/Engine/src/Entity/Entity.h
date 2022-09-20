#pragma once

#include "Renderer.h"
#include "Data Organizers/Vertex.h"


class Entity
{
public:
	Entity();
	Entity(Renderer* renderer);
	~Entity();
protected:
	Renderer* renderer;
	unsigned int* vBuffer;
	unsigned int* iBuffer;
};