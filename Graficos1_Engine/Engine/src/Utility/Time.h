#pragma once
#include "DLLManager.h"

class DLLEXPORT Time
{
public:
	Time();
	~Time();
	void Update();
	float GetDelta();
private:
	float lastFrameTime;
	float deltaTime;
};