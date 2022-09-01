#pragma once

#include "Window.h"
#include <list>

class Renderer
{
public:
	Renderer();
	Renderer(Window* window);
	~Renderer();
	void ClearScreen();
	void SwapWindowBuffers();
	void SetWindow(Window* window);
	void GetNewBuffer(unsigned int dataSize, void* data, bool dataIsStatic, unsigned int* buffer);
	void DeleteBuffer(unsigned int* buffer);
private:
	Window* window;
	std::list<unsigned int*>* bufferList;
};