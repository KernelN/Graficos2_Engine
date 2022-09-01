#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

Renderer::Renderer(){}

Renderer::Renderer(Window* window) 
{
	SetWindow(window);
}

Renderer::~Renderer(){}

void Renderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapWindowBuffers()
{
	//Check for windows existance
	if (!window)
	{
		std::cout << "RENDERER ERROR: Window Unexistant" << std::endl;
		return;
	}
	else if (!window->WindowExists())
	{
		std::cout << "RENDERER ERROR: GLFW Window Unexistant" << std::endl;
		return;
	}

	/* Swap front and back buffers */
	glfwSwapBuffers((GLFWwindow*)window->GetGLFWPointer());
}

void Renderer::SetWindow(Window* window)
{
	this->window = window;
}

#include <stack>
void Renderer::GetNewBuffer(unsigned int dataSize, void* data, bool dataIsStatic, unsigned int* buffer)
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

void Renderer::DeleteBuffer(unsigned int* buffer)
{
	//Get buffer using index and delete it
	glDeleteBuffers(1, buffer);
}
