#pragma once

#include "Renderer.h"

class Entity
{
public:
	Entity();
	Entity(Renderer* renderer);
	~Entity();
protected:
	Renderer* renderer;
	unsigned int* buffer;
	void SetBuffer(unsigned int dataSize, void* data, bool dataIsStatic);
};