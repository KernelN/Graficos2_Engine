#include "Square.h"

#include <glfw/include/GLFW/glfw3.h>
#include "Utility/Singleton.h"
#include "Renderer.h"

Square::Square(float vertexPos[4][2], float vertexCol[4][4], bool squareIsStatic)
{
	vertices = new Vertex[4];
	indices = new unsigned int[6];
	UpdateVertex(vertexPos, vertexCol);
	Singleton::GetRenderer()->GetChernoVertexBuffer(vertices, 4 * vertices->GetStride());
	Singleton::GetRenderer()->GetIndexBuffer(indices, 6);
	//Singleton::GetRenderer()->GetNewVertexBuffer
	//(
	//	vertices->GetComponentAmount(), //vertex components
	//	vertices->GetStride(), //stride
	//	squareIsStatic, //data is static
	//	0, //attribute id
	//	vertices, //vertices data
	//	indices, //indices
	//	4, //vertices amount
	//	6, //indices amount
	//	vBuffer, //vertex buffer
	//	iBuffer //index buffer
	//);
}

Square::~Square()
{
}

void Square::Draw()
{
	Singleton::GetRenderer()->Draw(6, modelID);
}

void Square::UpdateVertex(float vertexPos[4][2], float vertexCol[4][4])
{
	for (unsigned short i = 0; i < 4; i++)
	{
		//Set Vertex Pos
		vertices[i].position[0] = vertexPos[i][0];
		vertices[i].position[1] = vertexPos[i][1];
		
		//Set Vertex Col
		for (unsigned short j = 0; j < 4; j++)
		{
			vertices[i].color[j] = vertexCol[i][j];
		}
	}

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
}