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
	void LookAtTarget();
	void Translate(float x, float y, float z = 0);
	void Rotate(float angle, float angleY = 0, float angleZ = 0);
	void SetTranslation(float x, float y, float z = 0);
	void SetRotation(float angle, float angleY = 0, float angleZ = 0);
private:
	//CameraType type;
	Vector3 originalVecs[3];
	float originalMags[3];
	Vector3 vecs[3];
	Vector3 offset;
	Entity* followTarget;
};