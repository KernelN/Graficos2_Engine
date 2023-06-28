#pragma once
#include "DLLManager.h"
#include "Utility/Time.h"
#include "CollisionManager.h"
#include "Entity/Entity3D/Camera/Camera.h"

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
	Camera* GetActiveCamera();
protected:
	Time* time;
	CollisionManager* collisionManager;
private:
	void* inputManager;	
	void* window;
	void* renderer;
	bool isRunning = true; //Check if engine is running
};
