#include "Vertex.h"

#include <cstddef>

unsigned int Vertex::GetStride()
{
	return sizeof(float) * GetSize(pos);
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
	default:
		break;
	}
}