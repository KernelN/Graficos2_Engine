#pragma once

#include "Window.h"
#include "Renderer.h"
#include "DLLManager.h"

class DLLEXPORT BaseEngine
{
public:
	BaseEngine();
	~BaseEngine();
	bool IsRunning();
	void Loop();
	virtual void Draw();
private:
	Window* window;
	Renderer* renderer;
	bool isRunning = true; //Check if engine is running
};