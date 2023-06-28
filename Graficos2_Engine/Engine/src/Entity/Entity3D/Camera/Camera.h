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
	void SetFollow(Entity* target, Vector3 offset = zero);
	void FollowTarget();
private:
	//CameraType type;
	Vector3 originalVecs[3];
	Vector3 vecs[3];
	Vector3 offset;
	Entity* followTarget;
};