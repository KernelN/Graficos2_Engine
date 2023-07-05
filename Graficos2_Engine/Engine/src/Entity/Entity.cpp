#include "Entity.h"
#include "Utility/RendererSingleton.h"

#include <cmath>
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

void Entity::Translate(Vector3 trans)
{
	translation += trans;
	UpdateModel(true);
}

void Entity::Rotate(float angleZ, float angleY, float angleX)
{	
	rotation.x += angleX;
	rotation.y += angleY;
	rotation.z += angleZ;
	UpdateModel(true);
}

void Entity::Rotate(Vector3 rot)
{
	rotation += rot;
	UpdateModel(true);
}

void Entity::Scale(float x, float y, float z)
{
	scale.x += x;
	scale.y += y;
	scale.z += z;
	UpdateModel(true);	
}

void Entity::Scale(Vector3 scale)
{
	this->scale += scale;
	UpdateModel(true);
}

void Entity::SetTranslation(float x, float y, float z)
{
	translation.x = x;
	translation.y = y;
	translation.z = z;
	UpdateModel(true);
}

void Entity::SetTranslation(Vector3 trans)
{
	translation = trans;
	UpdateModel(true);
}

void Entity::SetRotation(float angle, float angleY, float angleZ)
{
	rotation.x = angle;
	rotation.y = angleY;
	rotation.z = angleZ;
	UpdateModel(true);
}

void Entity::SetRotation(Vector3 rot)
{
	rotation = rot;
	UpdateModel(true);
}

void Entity::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
	UpdateModel(true);	
}

void Entity::SetScale(Vector3 scale)
{
	this->scale = scale;
	UpdateModel(true);
}

void Entity::LookAt(Vector3 target)
{
	//Calculate quaternion rotation
	glm::quat rot = glm::quat(glm::vec3(rotation.x, rotation.y, rotation.z));

	//Get right
	// Vector3 rightVec = GetRight();
	// glm::vec3 right = glm::vec3(rightVec.x, rightVec.y, rightVec.z);

	//Get up
	const glm::vec3 worldUp = {0,1,0};
	// Vector3 upVec = GetUp();
	// glm::vec3 up = glm::vec3(upVec.x, upVec.y, upVec.z);
	
	//Set glm positions
	glm::vec3 pos = glm::vec3(translation.x, translation.y, translation.z);
	glm::vec3 targetPos = glm::vec3(target.x, target.y, target.z);

	//Calculate new directions
	glm::vec3 newForward = glm::normalize(targetPos - pos);
	glm::vec3 newRight = glm::normalize(glm::cross(newForward, worldUp));
	glm::vec3 newUp = glm::normalize(glm::cross(newRight, newForward));

	//Calculate new quaternion rotation
	glm::quat newRot = glm::quatLookAt(newForward, newUp);

	//Update rotation
	glm::vec3 newEuler = glm::eulerAngles(newRot);	
	SetRotation(newEuler.x, newEuler.y, newEuler.z);
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

Vector3 Entity::GetForward()
{
	//Calculate quaternion rotation
	glm::quat rot = glm::quat(glm::vec3(rotation.x, rotation.y, rotation.z));

	//Calculate forward
	glm::vec3 localForward = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 worldForward = rot * localForward;
	glm::vec3 forward = glm::normalize(worldForward);

	//Return forward
	return {forward.x, forward.y, forward.z};
}

Vector3 Entity::GetRight()
{
	//Calculate quaternion rotation
	glm::quat rot = glm::quat(glm::vec3(rotation.x, rotation.y, rotation.z));

	//Calculate right
	glm::vec3 localRight = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 worldRight = rot * localRight;
	glm::vec3 right = glm::normalize(worldRight);

	//Return right
	return { right.x, right.y, right.z };
}

Vector3 Entity::GetUp()
{
	//Calculate quaternion rotation
	glm::quat rot = glm::quat(glm::vec3(rotation.x, rotation.y, rotation.z));

	//Calculate up
	glm::vec3 localUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 worldUp = rot * localUp;
	glm::vec3 up = glm::normalize(worldUp);

	//Return up
	return { up.x, up.y, up.z };
}


const glm::mat4 identity = glm::mat4(1.0f);
const glm::vec3 xRotAxis = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 yRotAxis = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 zRotAxis = glm::vec3(0.0f, 0.0f, 1.0f);
void Entity::UpdateModel(bool isModelCreated)
{
	glm::mat4 trans = glm::translate(identity, glm::vec3(translation.x, translation.y, translation.z));
	
	glm::mat4 rot = glm::rotate(identity,  glm::radians(rotation.x), xRotAxis); // where x, y, z is axis of rotation (e.g. 0 1 0)
	rot = glm::rotate(rot, glm::radians(rotation.y), yRotAxis);
	rot = glm::rotate(rot, glm::radians(rotation.z), zRotAxis);

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
