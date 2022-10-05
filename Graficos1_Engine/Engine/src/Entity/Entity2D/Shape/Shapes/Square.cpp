#include "Square.h"

#include <glfw/include/GLFW/glfw3.h>
#include "Utility/Singleton.h"
#include "Renderer.h"

Square::Square(float vertexPos[8], bool triangleIsStatic)
{
	vertices = new Vertex[4];
	indices = new unsigned int[6];
	UpdateVertex(vertexPos);
	Singleton::GetRenderer()->GetNewVertexBuffer
	(
		vertices->GetComponentAmount(), //vertex components
		vertices->GetStride(), //stride
		triangleIsStatic, //data is static
		0, //attribute id
		vertices, //vertices data
		indices, //indices
		4, //vertices amount
		6, //indices amount
		vBuffer, //vertex buffer
		iBuffer //index buffer
	);
}

Square::~Square()
{
}

void Square::Draw()
{
	Singleton::GetRenderer()->Draw(6, modelID);
}

void Square::UpdateVertex(float vertexPos[8])
{
	for (int i = 0; i < 8; i++)
	{
		//set 2 positions per vertex, if i is even set X, else set Y
		if (i % 2 == 0)
		{
			
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

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;


}