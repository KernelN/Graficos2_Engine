#include "Entity.h"

Entity::Entity()
{
	renderer = globalRenderer; //get renderer from Base
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