#include "Triangle.h"

#include <GLFW/glfw3.h>

Triangle::Triangle(float vertexPos[6], bool triangleIsStatic)
{
	UpdateVertex(vertexPos);
	SetBuffer(6 * sizeof(float), this->vertexPos, triangleIsStatic);
}

Triangle::Triangle(float vertexPos[6], bool triangleIsStatic, Renderer* renderer)
	: Shape(renderer)
{
	UpdateVertex(vertexPos);
	SetBuffer(6 * sizeof(float), this->vertexPos, triangleIsStatic);
}

Triangle::~Triangle()
{
}

void Triangle::Draw()
{
	//https://docs.gl/gl4/glDrawArrays
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::UpdateVertex(float vertexPos[6])
{
	for (int i = 0; i < 6; i++)
	{
		this->vertexPos[i] = vertexPos[i];
	}
}
