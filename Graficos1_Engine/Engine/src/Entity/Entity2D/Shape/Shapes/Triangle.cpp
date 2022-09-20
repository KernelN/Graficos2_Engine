#include "Triangle.h"

#include <GLFW/glfw3.h>

Triangle::Triangle(float vertexPos[6], bool triangleIsStatic)
{
	vertices = new Vertex[3];
	indices = new unsigned int[3];
	UpdateVertex(vertexPos);
	renderer->GetNewVertexBuffer
	(
		vertices->GetComponentAmount(), //vertex components
		vertices->GetStride(), //stride
		triangleIsStatic, //data is static
		0, //attribute id
		vertices, //vertices data
		indices, //indices
		3, //vertices amount
		3, //indices amount
		vBuffer, //vertex buffer
		iBuffer //index buffer
	);
}

Triangle::Triangle(float vertexPos[6], bool triangleIsStatic, Renderer* renderer)
	: Shape(renderer)
{
	vertices = new Vertex[3];
	indices = new unsigned int[3];
	UpdateVertex(vertexPos);
	renderer->GetNewVertexBuffer
	(
		vertices->GetComponentAmount(), //components per vertex
		vertices->GetStride(), //stride
		triangleIsStatic, //data is static
		0, //attribute id
		vertices, //vertices data
		indices, //indices
		3, //vertices amount
		3, //indices amount
		vBuffer, //vertex buffer
		iBuffer //index buffer
	); 
}

Triangle::~Triangle()
{
}

void Triangle::Draw()
{
	//https://docs.gl/gl4/glDrawArrays
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	glDrawArrays(GL_TRIANGLES, 0, 3); //SEND TO RENDERER, SHOULDN'T BE IN TRIANGLE
}

void Triangle::UpdateVertex(float vertexPos[6])
{
	for (int i = 0; i < 6; i++)
	{ 
		//set 2 positions per vertex, if i is even set X, else set Y
		if (i % 2 == 0)
		{
			indices[i / 2] = i / 2;
			vertices[i / 2].position[0] = vertexPos[i];

			/*vertices[i / 2].color[0] = 1.0;
			vertices[i / 2].color[1] = 0.0;
			vertices[i / 2].color[2] = 0.0;
			vertices[i / 2].color[3] = 1.0;*/
		}
		else
		{
			vertices[i / 2].position[1] = vertexPos[i];
		}
	}
}