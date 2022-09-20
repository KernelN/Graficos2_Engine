#include "Entity.h"

Entity::Entity()
{
	renderer = nullptr; //get renderer from Base
	vBuffer = new unsigned int;
	iBuffer = new unsigned int;
}

Entity::Entity(Renderer* renderer)
{
	this->renderer = renderer;
	vBuffer = new unsigned int;
	iBuffer = new unsigned int;
}

Entity::~Entity() 
{
	if (vBuffer != nullptr)
	{ 
		//Delete buffer from renderer
		renderer->DeleteBuffer(vBuffer);
	}

	if (iBuffer != nullptr)
	{
		//Delete buffer from renderer
		renderer->DeleteBuffer(iBuffer);
	}
}