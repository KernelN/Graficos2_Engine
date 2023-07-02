#pragma once
#include "Entity/Entity3D/Entity3D.h"

class DLLEXPORT Cube : public Entity3D
{
public:
    Cube(float vertexCol[4][4]);
    ~Cube();
	void Draw();
private:
    Vertex* vertices;
    unsigned int* indices;
};