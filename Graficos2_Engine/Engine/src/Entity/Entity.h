#pragma once

#include "DLLManager.h"
#include "Data Organizers/Vertex.h"
#include "Data Organizers/Vectors/Vector3.h"
#include "Data Organizers/Buffer/Buffer.h"

class DLLEXPORT Entity
{
public:
	Entity();
	~Entity();
	void Translate(float x, float y, float z = 0);
	void Translate(Vector3 trans);
	void Rotate(float angle, float angleY = 0, float angleZ = 0);
	void Rotate(Vector3 rot);
	void Scale(float x, float y, float z = 0);
	void Scale(Vector3 scale);

	void SetTranslation(float x, float y, float z = 0);
	void SetTranslation(Vector3 trans);
	void SetRotation(float angle, float angleY = 0, float angleZ = 0);
	void SetRotation(Vector3 rot);
	void SetScale(float x, float y, float z = 0);
	void SetScale(Vector3 scale);

	void LookAt(Vector3 target);
	
	Vector3 GetTranslation();
	Vector3 GetRotation();
	Vector3 GetScale();

	Vector3 GetForward();
	Vector3 GetRight();
	Vector3 GetUp();
protected:
	void UpdateModel(bool isModelCreated);

	unsigned int* vBuffer;
	unsigned int* iBuffer;
	unsigned int modelID;

	Vector3 translation;
	Vector3 rotation;
	Vector3 scale;
	Vector4 trs[4];
};