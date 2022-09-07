#pragma once
struct Vertex
{
public:
	enum Attributes { pos, col, _count };
	float position[2];
	float color[4];
	unsigned int GetStride();
	unsigned int GetIndex(Attributes attribute);
	unsigned int GetSize(Attributes attribute);
	unsigned int GetOffset(Attributes attribute);
};