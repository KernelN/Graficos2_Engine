#pragma once
struct Vertex
{
public:
	enum Attributes { pos };
	float position[2];
	unsigned int GetStride();
	unsigned int GetIndex(Attributes attribute);
	unsigned int GetSize(Attributes attribute);
	unsigned int GetOffset(Attributes attribute);
};