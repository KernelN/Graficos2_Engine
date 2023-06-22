#pragma once

#include "Entity/Entity3D/Entity3D.h"

//enum CameraType { FirstPerson, ThirdPerson};

class DLLEXPORT Camera : public Entity3D
{
public:
	Camera();
	~Camera();
	void Update();
	void GetView(Vector3 cameraVecs[3]);
private:
	//CameraType type;
	Vector3 vecs[3];
	//void UpdateCameraPos();
};