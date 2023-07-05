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
	void FollowTarget(bool rotateWithTarget = false);
	void LookAtTarget();
	
	void Translate(float x, float y, float z = 0);
	void Translate(Vector3 trans);
	void Rotate(float angle, float angleY = 0, float angleZ = 0);
	void Rotate(Vector3 rot);
	
	void SetTranslation(float x, float y, float z = 0);
	void SetTranslation(Vector3 trans);
	void SetRotation(float angle, float angleY = 0, float angleZ = 0);
	void SetRotation(Vector3 rot);
private:
	//CameraType type;
	Vector3 originalVecs[3];
	float originalMags[3];
	Vector3 vecs[3];
	Vector3 offset;
	Entity* followTarget;

	void UpdateEyePos();
	void UpdateEyeTarget();
	void UpdateEyeUp();
};