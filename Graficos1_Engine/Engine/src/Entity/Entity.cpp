#include "Entity.h"

Entity::Entity()
{
	renderer = nullptr; //get renderer from Base
	buffer = nullptr;
}

Entity::Entity(Renderer* renderer)
{
	this->renderer = renderer;
	buffer = nullptr;
}

Entity::~Entity() 
{
	if (buffer != nullptr)
	{ 
		//Delete buffer from renderer
		renderer->DeleteBuffer(buffer);
	}
	delete[] vertexes;
}