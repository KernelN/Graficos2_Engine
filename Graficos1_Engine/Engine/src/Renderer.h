#pragma once

#include "Window.h"

class Renderer
{
public:
	Renderer();
	Renderer(Window* window);
	~Renderer();
	void ClearScreen();
	void SwapBuffers();
	void SetWindow(Window* window);
private:
	Window* window;
};