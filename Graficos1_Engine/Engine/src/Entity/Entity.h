#pragma once

#include "Renderer.h"
#include "Data Organizers/Vertex.h"
#include "DLLManager.h"


class DLLEXPORT Entity
{
public:
	Entity();
	~Entity();
protected:
	Renderer* renderer;
	unsigned int* vBuffer;
	unsigned int* iBuffer;
};