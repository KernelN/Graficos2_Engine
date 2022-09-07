#include "Entity.h"

Entity::Entity()
{
	renderer = nullptr; //get renderer from Base
	buffer = new unsigned int;
}

Entity::Entity(Renderer* renderer)
{
	this->renderer = renderer;
	buffer = new unsigned int;
}

Entity::~Entity() 
{
	if (buffer != nullptr)
	{ 
		//Delete buffer from renderer
		renderer->DeleteBuffer(buffer);
	}
}