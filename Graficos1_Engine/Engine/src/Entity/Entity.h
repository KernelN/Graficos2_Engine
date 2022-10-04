#pragma once

//#include "Renderer.h"
#include "Data Organizers/Vertex.h"
#include "DLLManager.h"
#include "Data Organizers/Vector2.h"

class DLLEXPORT Entity
{
public:
	Entity();
	~Entity();
	void Translate(float x, float y);
	void Rotate(float angle);
	void Scale(float x, float y);

protected:
	void funnyTransformationStuff();
	void funnyTransformUpdate();
	void UpdateModel(bool isModelCreated);

	unsigned int* vBuffer;
	unsigned int* iBuffer;
	unsigned int modelID;


	Vector2 translation;
	float rotation;
	Vector2 scale;

	
};