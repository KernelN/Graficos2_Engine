#include "Triangle.h"

#include "Utility/Singleton.h"
#include "Renderer.h"

Triangle::Triangle(float vertexPos[6], bool triangleIsStatic)
{
	vertices = new Vertex[3];
	indices = new unsigned int[3];
	UpdateVertex(vertexPos);
	//Singleton::GetRenderer()->GetNewVertexBuffer
	//(
	//	vertices->GetComponentAmount(), //vertex components
	//	vertices->GetStride(), //stride
	//	triangleIsStatic, //data is static
	//	0, //attribute id
	//	vertices, //vertices data
	//	indices, //indices
	//	3, //vertices amount
	//	3, //indices amount
	//	vBuffer, //vertex buffer
	//	iBuffer //index buffer
	//);
}

Triangle::~Triangle()
{
}

void Triangle::Draw()
{
	Singleton::GetRenderer()->Draw(3, modelID);
}

//MUST UPDATE
void Triangle::UpdateVertex(float vertexPos[6])
{
	//for (int i = 0; i < 6; i++)
	//{ 
	//	//set 2 positions per vertex, if i is even set X, else set Y
	//	if (i % 2 == 0)
	//	{
	//		indices[i / 2] = i / 2;
	//		vertices[i / 2].position[0] = vertexPos[i];

	//		/*vertices[i / 2].color[0] = 1.0;
	//		vertices[i / 2].color[1] = 0.0;
	//		vertices[i / 2].color[2] = 0.0;
	//		vertices[i / 2].color[3] = 1.0;*/
	//	}
	//	else
	//	{
	//		vertices[i / 2].position[1] = vertexPos[i];
	//	}
	//}
}