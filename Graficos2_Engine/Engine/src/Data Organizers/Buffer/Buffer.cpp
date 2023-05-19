#include "Buffer.h"
#include <glew/include/GL/glew.h>

Buffer::Buffer()
{

}

Buffer::~Buffer()
{
	//Get buffer using index and delete it
	glDeleteBuffers(1, buffer);
}