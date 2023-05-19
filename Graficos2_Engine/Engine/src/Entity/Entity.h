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
	void Rotate(float angle, float angleY = 0, float angleZ = 0);
	void Scale(float x, float y, float z = 0);

	Vector3 GetTranslation();
	Vector3 GetRotation();
	Vector3 GetScale();

protected:
	void UpdateModel(bool isModelCreated);

	unsigned int* vBuffer;
	unsigned int* iBuffer;
	unsigned int modelID;


	Vector3 translation;
	Vector3 rotation;
	Vector3 scale;
};