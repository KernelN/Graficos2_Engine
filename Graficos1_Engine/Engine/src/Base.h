#pragma once
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
	void* window;
	void* renderer;
	bool isRunning = true; //Check if engine is running
};