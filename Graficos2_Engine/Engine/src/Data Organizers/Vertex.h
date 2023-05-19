#pragma once
#include "DLLManager.h"
#include "Data Organizers/Vector2.h"
#include "Data Organizers/Vectors/Vector4.h"

struct DLLEXPORT Vertex
{
public:
	Vertex();

	enum Attributes { pos, col, /*uv,*/ _count };
	bool initedVars[_count];
	unsigned int GetStride();
	unsigned int GetComponentAmount();
	unsigned int GetIndex(Attributes attribute);
	unsigned int GetSize(Attributes attribute);
	unsigned int GetOffset(Attributes attribute);
	void SetPos(float _position[2]);
	void SetColor(float _color[4]);
	//void SetUV(float _textCoord[2]);
	//void SetPos(Vector2 _position);
	//void SetColor(Vector4 _color);
	//void SetUV(Vector2 _textCoord);
	//Make Getters, maybe use Vec2 & Vec4
private:
	float position[2];
	float color[4];
	//float textCoord[2];
	//Vector2 position;
	//Vector4 color;
	//Vector2 textCoord;
};