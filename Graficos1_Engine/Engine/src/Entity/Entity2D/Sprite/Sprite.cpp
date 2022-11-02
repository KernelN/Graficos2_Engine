#include "Sprite.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Utility/stb_image.h"
#include <glew/include/GL/glew.h>
#include <Utility/Singleton.h>

Sprite::Sprite(const std::string& path)
{
	rendererID = 0;
	filePath = path;
	localBuffer = nullptr;
	width = 0;
	height = 0;
	bitsPerPixel = 0;

	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(filePath.c_str(), &width, &height, &bitsPerPixel, 4);

	glGenTextures(1, &rendererID);
	glBindTexture(GL_TEXTURE_2D, rendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (localBuffer)
		stbi_image_free(localBuffer);


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

	Bind();
	Singleton::GetRenderer()->SetSprite(0);
}

Sprite::~Sprite()
{
	glDeleteTextures(1, &rendererID);
}

void Sprite::Bind(unsigned int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, rendererID);
}

void Sprite::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Sprite::Draw()
{
	Singleton::GetRenderer()->Draw(6, modelID);
}