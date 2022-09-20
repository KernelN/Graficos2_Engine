#pragma once

#include "Window.h"
#include "Renderer.h"
#include "DLLManager.h"

class DLLEXPORT Base
{
public:
	Base();
	~Base();
	bool IsRunning();
	void Loop();
	virtual void Draw();
private:
	Window* window;
	Renderer* renderer;
	bool isRunning = true; //Check if engine is running
};