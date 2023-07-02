#include "Cube.h"

#include "Utility/RendererSingleton.h"

Cube::Cube(float vertexCol[4][4])
{
    float vertexPos[8][3] =
    {
        {-1, -1, -1}, // Vertex 0 (DBL - Down Back Left)
        {1, -1, -1},  // Vertex 1 (DBR - Down Back Right)
        {1, 1, -1},   // Vertex 2 (DFR - Down Front Right)
        {-1, 1, -1},  // Vertex 3 (DFL - Down Front Left)
        {-1, -1, 1},  // Vertex 4 (UBL - Up Back Left)
        {1, -1, 1},   // Vertex 5 (UBR - Up Back Right)
        {1, 1, 1},    // Vertex 6 (UFR - Up Front Right)
        {-1, 1, 1}    // Vertex 7 (UFL - Up Front Left)
    };

    unsigned int tempIndices[36] =
    {
        // Face 1 (front)
        0, 1, 2,
        2, 3, 0,

        // Face 2 (back)
        4, 5, 6,
        6, 7, 4,

        // Face 3 (left)
        0, 3, 7,
        7, 4, 0,

        // Face 4 (right)
        1, 5, 6,
        6, 2, 1,

        // Face 5 (top)
        3, 2, 6,
        6, 7, 3,

        // Face 6 (bottom)
        0, 4, 5,
        5, 1, 0
    };

    float tempVertices[8][7];
    for (unsigned short i = 0; i < 8; i++)
    {
        for (unsigned short j = 0; j < 3; j++)
        {
            tempVertices[i][j] = vertexPos[i][j];
        }
        for (unsigned short j = 3; j < 7; j++)
        {
            tempVertices[i][j] = vertexCol[i][j-3];
        }
    }

    //vertices = new Vertex[4];
    indices = new unsigned int[36];
    //UpdateVertex(vertexCol);

    *vBuffer = RendererSingleton::GetRenderer()->GetNewVertexBuffer(tempVertices, 8 * (sizeof(float) * 3 + sizeof(float) * 4));
    *iBuffer = RendererSingleton::GetRenderer()->GetNewIndexBuffer(tempIndices, 36);
}

Cube::~Cube()
{
    if (vertices != nullptr)
        delete[] vertices;
}

void Cube::Draw()
{
    RendererSingleton::GetRenderer()->Draw(*vBuffer, *iBuffer, modelID);
}
