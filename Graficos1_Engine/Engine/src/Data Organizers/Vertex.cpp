#include "Vertex.h"

#include <cstddef>

Vertex::Vertex()
{
	for (unsigned short i = 0; i < 2; i++)
	{
		position[i] = 0;
		//textCoord[i] = 0;
	}
	for (unsigned short i = 0; i < 4; i++)
	{
		color[i] = 0;
	}
	//position = { 0,0 };
	//color = { 0,0,0,0 };
	//textCoord = { 0,0 };

	for (unsigned short i = 0; i < _count; i++)
	{
		initedVars[i] = false;
	}
}
unsigned int Vertex::GetStride()
{
	return sizeof(float) * GetSize(pos) + sizeof(float) * GetSize(col);// +sizeof(float) * GetSize(uv);
}

unsigned int Vertex::GetComponentAmount()
{
	return GetSize(pos) + GetSize(col);// + GetSize(uv);
}

unsigned int Vertex::GetIndex(Attributes attribute)
{	
	return (unsigned int)attribute;
}

unsigned int Vertex::GetSize(Attributes attribute)
{
	switch (attribute)
	{
	case Vertex::pos:
		return initedVars[pos] ? 2 : 0;
	case Vertex::col:
		return initedVars[col] ? 4 : 0;
	//case Vertex::uv:
	//	return initedVars[uv] ? 2 : 0;
	default:
		break;
	}
	return 0;
}

unsigned int Vertex::GetOffset(Attributes attribute)
{
	switch (attribute)
	{
	case Vertex::pos:
		return offsetof(Vertex, position);
	case Vertex::col:
		return offsetof(Vertex, color);
	//case Vertex::uv:
	//	return offsetof(Vertex, textCoord);
	default:
		break;
	}
}

void Vertex::SetPos(float _position[2])
{
	for (short i = 0; i < 2; i++)
	{
		position[i] = _position[i];
	}

	initedVars[pos] = true;
}

void Vertex::SetColor(float _color[4])
{
	for (short i = 0; i < 4; i++)
	{
		color[i] = _color[i];
	}

	initedVars[col] = true;
}

//void Vertex::SetUV(float _textCoord[2])
//{
//	for (short i = 0; i < 2; i++)
//	{
//		textCoord[i] = _textCoord[i];
//	}
//
//	initedVars[uv] = true;
//}

//void Vertex::SetPos(Vector2 _position)
//{
//	position = _position;
//
//	initedVars[pos] = true;
//}
//
//void Vertex::SetColor(Vector4 _color)
//{
//	color = _color;
//
//	initedVars[col] = true;
//}
//
//void Vertex::SetUV(Vector2 _textCoord)
//{
//	textCoord = _textCoord;
//
//	initedVars[uv] = true;
//}