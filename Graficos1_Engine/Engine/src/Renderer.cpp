#include "Renderer.h"

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

void Renderer::SwapBuffers()
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