#pragma once

#include "Entity/Entity3D/Entity3D.h"

class Camera : public Entity3D
{
public:
	Camera();
	~Camera();
	void Update();
private:
	void UpdateCameraPos();
};