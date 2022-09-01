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
	Vertex* vertexes;
	Renderer* renderer;
	unsigned int* buffer;
};