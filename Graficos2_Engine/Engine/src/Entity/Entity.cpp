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
	
	translation = { 0, 0, 0 };
	rotation = { 0, 0, 0 };
	scale = { 1, 1, 1 };

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

void Entity::Translate(float x, float y, float z)
{
	translation.x += x;
	translation.y += y;
	translation.z += z;
	UpdateModel(true);
}

void Entity::Rotate(float angleZ, float angleY, float angleX)
{	
	rotation.x += angleX;
	rotation.y += angleY;
	rotation.z += angleZ;
	UpdateModel(true);
}

void Entity::Scale(float x, float y, float z)
{
	scale.x += x;
	scale.y += y;
	scale.z += z;
	UpdateModel(true);	
}

Vector3 Entity::GetTranslation()
{
	return translation;
}

Vector3 Entity::GetRotation()
{
	return rotation;
}

Vector3 Entity::GetScale()
{
	return scale;
}


const glm::mat4 identity = glm::mat4(1.0f);
const glm::vec3 xRotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 yRotAxis = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 zRotAxis = glm::vec3(0.0f, 0.0f, 1.0f);
void Entity::UpdateModel(bool isModelCreated)
{
	glm::mat4 trans = glm::translate(identity, glm::vec3(translation.x, translation.y, translation.z));
	
	glm::mat4 rot = glm::rotate(identity, (rotation.x * 3.14f) / 180, xRotAxis); // where x, y, z is axis of rotation (e.g. 0 1 0)
	rot = glm::rotate(rot, (rotation.y * 3.14f) / 180, yRotAxis);
	rot = glm::rotate(rot, (rotation.z * 3.14f) / 180, zRotAxis);

	//glm::mat4 rot = glm::rotate(glm::mat4(1.0f), (rotation.z * 3.14f) / 180, glm::vec3(0, 0, 1)); // where x, y, z is axis of rotation (e.g. 0 1 0)
	//rot = glm::rotate(rot, (rotation.y * 3.14f) / 180, glm::vec3(0, 1, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
	//rot = glm::rotate(rot, (rotation.x * 3.14f) / 180, glm::vec3(1, 0, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
	
	glm::mat4 scal = glm::scale(identity, glm::vec3(scale.x / 2, scale.y / 2, scale.z / 2));

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
