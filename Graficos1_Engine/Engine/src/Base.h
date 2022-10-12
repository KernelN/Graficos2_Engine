#pragma once
#include "DLLManager.h"


class DLLEXPORT BaseEngine
{
public:
	BaseEngine();
	~BaseEngine();
	bool IsRunning();
	void Loop();
	virtual void OnLoop();
	virtual void Draw();
	bool IsKeyPressed(unsigned short KeyCode);
private:
	void* inputManager;
	void* window;
	void* renderer;
	bool isRunning = true; //Check if engine is running
};