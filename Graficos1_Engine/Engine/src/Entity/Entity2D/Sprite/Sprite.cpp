#include "Sprite.h"

#include "Utility/Singleton.h"

Sprite::Sprite(const std::string& path)
{
	rendererID = 0;
	filePath = path;
	localBuffer = nullptr;
	width = 0;
	height = 0;
	bitsPerPixel = 0;
	
	Singleton::GetRenderer()->GetNewSprite(path, &width, &height, &bitsPerPixel, &rendererID);

	float vertexPos[4][2] =
	{
		{-1, -1},
		{1, -1},
		{1, 1},
		{-1, 1}
	};
	float uvPos[4][2] =
	{
		{0, 0},
		{1, 0},
		{1, 1},
		{0, 1}
	};
	unsigned int indices[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	float tempVertices[4][4];
	for (unsigned short i = 0; i < 4; i++)
	{
		for (unsigned short j = 0; j < 2; j++)
		{
			tempVertices[i][j] = vertexPos[i][j];
		}
		for (unsigned short j = 2; j < 4; j++)
		{
			tempVertices[i][j] = uvPos[i][j - 2];
		}
	}

	Singleton::GetRenderer()->GetNewVertexBuffer(tempVertices, 4 * (sizeof(float) * 2 + sizeof(float) * 2));
	Singleton::GetRenderer()->GetNewIndexBuffer(indices, 6);

	Singleton::GetRenderer()->BindSprite(0, rendererID);
	Singleton::GetRenderer()->SetSprite(0);
}

Sprite::Sprite(const std::string& path, const int uvOffset[4][2])
{
	rendererID = 0;
	filePath = path;
	localBuffer = nullptr;
	width = 0;
	height = 0;
	bitsPerPixel = 0;

	Singleton::GetRenderer()->GetNewSprite(path, &width, &height, &bitsPerPixel, &rendererID);

	float vertexPos[4][2] =
	{
		{-1, -1},
		{1, -1},
		{1, 1},
		{-1, 1}
	};
	float uvPos[4][2] =
	{
		{0, 0},
		{1, 0},
		{1, 1},
		{0, 1}
	};
	unsigned int indices[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	float tempVertices[4][4];
	for (unsigned short i = 0; i < 4; i++)
	{
		for (unsigned short j = 0; j < 2; j++)
		{
			tempVertices[i][j] = vertexPos[i][j];
		}
		for (unsigned short j = 2; j < 4; j++)
		{
			tempVertices[i][j] = uvPos[i][j - 2] + uvOffset[i][j - 2];
		}
	}

	Singleton::GetRenderer()->GetNewVertexBuffer(tempVertices, 4 * (sizeof(float) * 2 + sizeof(float) * 2));
	Singleton::GetRenderer()->GetNewIndexBuffer(indices, 6);

	Singleton::GetRenderer()->BindSprite(0, rendererID);
	Singleton::GetRenderer()->SetSprite(0);
}

Sprite::~Sprite()
{
	Singleton::GetRenderer()->DeleteSprite(&rendererID);
}

void Sprite::Draw()
{
	Singleton::GetRenderer()->Draw(6, modelID);
}