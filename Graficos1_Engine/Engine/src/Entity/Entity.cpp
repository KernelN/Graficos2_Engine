#include "Entity.h"
#include "Utility/Singleton.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
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
		Singleton::GetRenderer()->DeleteBuffer(vBuffer);
	}

	if (iBuffer != nullptr)
	{
		//Delete buffer from renderer
		Singleton::GetRenderer()->DeleteBuffer(iBuffer);
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

//https://learnopengl.com/Getting-started/Transformations
void Entity::funnyTransformationStuff()
{
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	vec = trans * vec;

	//Make function in renderer for transform location
	/*unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));*/

}

//https://learnopengl.com/Getting-started/Transformations
void Entity::funnyTransformUpdate()
{
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Entity::UpdateModel(bool isModelCreated)
{
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, 0.0f));
	glm::mat4 rot = glm::rotate(glm::mat4(1.0f), (rotation * 3.14f) / 180, glm::vec3(0, 1, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
	glm::mat4 scal = glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, 0.0f));

	glm::mat4 model = scal * rot * trans;

	if (isModelCreated)
	{
		Singleton::GetRenderer()->SetModel(model, modelID);
	}
	else
	{
		modelID = Singleton::GetRenderer()->GetNewModelID(model);
	}
}
