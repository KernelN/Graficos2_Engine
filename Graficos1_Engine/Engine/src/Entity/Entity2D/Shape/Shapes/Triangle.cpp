#include "Triangle.h"

#include <GLFW/glfw3.h>

Triangle::Triangle(float vertexPos[6], bool triangleIsStatic)
{
	vertices = new Vertex[6];
	UpdateVertex(vertexPos);
	renderer->GetNewVertexBuffer(vertices->_count, 3 * vertices->GetStride(), vertices, triangleIsStatic, buffer);
}

Triangle::Triangle(float vertexPos[6], bool triangleIsStatic, Renderer* renderer)
	: Shape(renderer)
{
	vertices = new Vertex[6];
	UpdateVertex(vertexPos);
	renderer->GetNewVertexBuffer(vertices->_count, 3 * vertices->GetStride(), vertices, triangleIsStatic, buffer);
}

Triangle::~Triangle()
{
}

void Triangle::Draw()
{
	//https://docs.gl/gl4/glDrawArrays
	glDrawArrays(GL_TRIANGLES, 0, 3); //SEND TO RENDERER, SHOULDN'T BE IN TRIANGLE
}

void Triangle::UpdateVertex(float vertexPos[6])
{
	for (int i = 0; i < 6; i++)
	{ 
		//set 2 positions per vertex, if i is even set X, else set Y
		if (i % 2 == 0)
		{
			vertices[i / 2].position[0] = vertexPos[i];

			vertices[i / 2].color[0] = 1.0;
			vertices[i / 2].color[1] = 0.0;
			vertices[i / 2].color[2] = 0.0;
			vertices[i / 2].color[3] = 1.0;
		}
		else
		{
			vertices[i / 2].position[1] = vertexPos[i];
		}
	}
}