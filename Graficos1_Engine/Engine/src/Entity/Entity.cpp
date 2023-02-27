#include "Entity.h"
#include "Utility/RendererSingleton.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Renderer.h>

Entity::Entity()
{
	//renderer = globalRenderer; //get renderer from Base
	vBuffer = new unsigned int;
	iBuffer = new unsigned int;
	
	translation = { 0, 0 };
	rotation = 0;
	scale = { 1, 1 };

	UpdateModel(false);

}

Entity::~Entity() 
{
	if (vBuffer != nullptr)
	{ 
		//Delete buffer from renderer
		RendererSingleton::GetRenderer()->DeleteBuffer(vBuffer);
	}

	if (iBuffer != nullptr)
	{
		//Delete buffer from renderer
		RendererSingleton::GetRenderer()->DeleteBuffer(iBuffer);
	}
}

void Entity::Translate(float x, float y)
{
	translation.x += x;
	translation.y += y;
	UpdateModel(true);
}

void Entity::Rotate(float angle)
{	
	rotation += angle;
	UpdateModel(true);
}

void Entity::Scale(float x, float y)
{
	scale.x += x;
	scale.y += y;
	UpdateModel(true);	
}

Vector2 Entity::GetTranslation()
{
	return translation;
}

float Entity::GetRotation()
{
	return rotation;
}

Vector2 Entity::GetScale()
{
	return scale;
}

void Entity::UpdateModel(bool isModelCreated)
{
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, 0.0f));
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), (rotation * 3.14f) / 180, glm::vec3(0, 0, 1)); // where x, y, z is axis of rotation (e.g. 0 1 0)
	glm::mat4 scal = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x / 2, scale.y / 2, 0.0f));

	glm::mat4 model = trans * rot * scal;

	if (isModelCreated)
	{
		RendererSingleton::GetRenderer()->SetModel(model, modelID);
	}
	else
	{
		modelID = RendererSingleton::GetRenderer()->GetNewModelID(model);
	}
}
