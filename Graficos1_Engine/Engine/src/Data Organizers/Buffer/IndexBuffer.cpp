#include "Data Organizers/Buffer/IndexBuffer.h"

#include "glew/include/GL/glew.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(unsigned int* data, unsigned int count)
	: count(count)
{
	assert(sizeof(unsigned int) == sizeof(GLuint));

	//Ask openGL for X buffers (1 in this case) and links them to a uint pointer
	//https://docs.gl/gl4/glGenBuffers
	glGenBuffers(1, &rendererID);

	//Select buffer and set it as array buffer (ideal to work with vertexes)
	//https://docs.gl/gl4/glBindBuffer
	//unsigned int vBufferData = *id;
	glBindBuffer(GL_ARRAY_BUFFER, rendererID); //maybe problems?

	//Send data to buffer
	//https://docs.gl/gl4/glBufferData
	//GLenum dataUsage = dataIsStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;
	//unsigned int vDataSize = vAmount * stride;
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); //may be a problem
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &rendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}