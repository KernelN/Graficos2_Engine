#include "Vertex.h"

#include <cstddef>

unsigned int Vertex::GetStride()
{
	return sizeof(float) * GetSize(pos) + sizeof(float) * GetSize(col);
}

unsigned int Vertex::GetComponentAmount()
{
	return GetSize(pos) + GetSize(col);
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
		return 2;
		break;
	case Vertex::col:
		return 4;
		break;
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
		break;
	case Vertex::col:
		return offsetof(Vertex, color);
		break;
	default:
		break;
	}
}