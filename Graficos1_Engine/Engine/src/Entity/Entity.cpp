#include "Entity.h"
#include <GL/glew.h>
//#include <GLFW/glfw3.h>

Entity::Entity()
{
	renderer = nullptr;
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
		glDeleteBuffers(1, buffer);
	}
}

void Entity::SetBuffer(unsigned int dataSize, void* data, bool dataIsStatic)
{
	//Ask openGL for X buffers (1 in this case) and links them to a uint pointer
	//https://docs.gl/gl4/glGenBuffers
	glGenBuffers(1, buffer);
	
	//Select buffer and set it as array buffer (ideal to work with vertexes)
	//https://docs.gl/gl4/glBindBuffer
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	
	//Send data to buffer
	//https://docs.gl/gl4/glBufferData
	GLenum dataUsage = dataIsStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, dataUsage);
}
