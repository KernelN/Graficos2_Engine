#pragma once
#include "DLLManager.h"
#include "Utility/Time.h"
#include "CollisionManager.h"

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
protected:
	Time* time;
	CollisionManager* collisionManager;
private:
	void* inputManager;	
	void* window;
	void* renderer;
	bool isRunning = true; //Check if engine is running
};