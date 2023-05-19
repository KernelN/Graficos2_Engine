#include "Square.h"

#include "Utility/RendererSingleton.h"
#include "Renderer.h"

Square::Square(float vertexCol[4][4], bool squareIsStatic)
{
	float vertexPos[4][2] =
	{
		{-1, -1},
		{1, -1},
		{1, 1},
		{-1, 1}
	};
	unsigned int tempIndices[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	float tempVertices[4][6];
	for (unsigned short i = 0; i < 4; i++)
	{
		for (unsigned short j = 0; j < 2; j++)
		{
			tempVertices[i][j] = vertexPos[i][j];
		}
		for (unsigned short j = 2; j < 6; j++)
		{
			tempVertices[i][j] = vertexCol[i][j-2];
		}
	}

	//vertices = new Vertex[4];
	indices = new unsigned int[6];
	//UpdateVertex(vertexCol);

	*vBuffer = RendererSingleton::GetRenderer()->GetNewVertexBuffer(tempVertices, 4 * (sizeof(float) * 2 + sizeof(float) * 4));
	*iBuffer = RendererSingleton::GetRenderer()->GetNewIndexBuffer(tempIndices, 6);
}

Square::~Square()
{
}

void Square::Draw()
{
	RendererSingleton::GetRenderer()->Draw(*vBuffer, *iBuffer, modelID);
}

void Square::UpdateVertex(float vertexCol[4][4])
{
	float vertexPos[4][2] =
	{
		{-1, -1},
		{1, -1},
		{1, 1},
		{-1, 1}
	};

	for (unsigned short i = 0; i < 4; i++)
	{
		//Set Vertex Pos
		//vertices[i].SetPos({ vertexPos[i][0],vertexPos[i][1] });
		vertices[i].SetPos(vertexPos[i]);
		//vertices[i].position[0] = vertexPos[i][0];
		//vertices[i].position[1] = vertexPos[i][1];
		
		//Set Vertex Col
		//Vector4 color;
		//color.x = vertexCol[i][0];
		//color.y = vertexCol[i][1];
		//color.z = vertexCol[i][2];
		//color.w = vertexCol[i][3];
		//vertices[i].SetColor(color);
		vertices[i].SetColor(vertexCol[i]);
		//for (unsigned short j = 0; j < 4; j++)
		//{
		//	vertices[i].color[j] = vertexCol[i][j];
		//}
	}

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
}