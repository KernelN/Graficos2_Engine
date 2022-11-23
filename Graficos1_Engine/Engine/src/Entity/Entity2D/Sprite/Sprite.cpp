#include "Sprite.h"

#include "Utility/Singleton.h"

Sprite::Sprite(const std::string& path)
{
	rendererID = 0;
	filePath = path;
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
		{0, 0}, //bot left
		{1, 0}, //bot right
		{1, 1}, //top right
		{0, 1}  //top left
	};
	unsigned int indices[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	for (unsigned short i = 0; i < 4; i++)
	{
		for (unsigned short j = 0; j < 2; j++)
		{
			vertices[i][j] = vertexPos[i][j];
		}
		for (unsigned short j = 2; j < 4; j++)
		{
			vertices[i][j] = uvPos[i][j - 2];
		}
	}

	*vBuffer = Singleton::GetRenderer()->GetNewVertexBuffer(vertices, 4 * (sizeof(float) * 2 + sizeof(float) * 2));
	*iBuffer = Singleton::GetRenderer()->GetNewIndexBuffer(indices, 6);

	Singleton::GetRenderer()->BindSprite(0, rendererID);
	Singleton::GetRenderer()->SetSprite(rendererID);
}

Sprite::Sprite(const std::string& path, int imgSize[2])
{
	rendererID = 0;
	filePath = path;
	width = imgSize[0];
	height = imgSize[1];
	bitsPerPixel = 0;

	Singleton::GetRenderer()->GetNewSprite(path, &width, &height, &bitsPerPixel, &rendererID);

	float widthHeightRatio = width / height;
	float adjustedX = 0.5f * widthHeightRatio;

	float vertexPos[4][2] =
	{
		{-adjustedX, -1},
		{adjustedX, -1},
		{adjustedX, 1},
		{-adjustedX, 1}
	};
	float uvPos[4][2] =
	{
		{0, 0}, //bot left
		{1, 0}, //bot right
		{1, 1}, //top right
		{0, 1}  //top left
	};
	unsigned int indices[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	for (unsigned short i = 0; i < 4; i++)
	{
		for (unsigned short j = 0; j < 2; j++)
		{
			vertices[i][j] = vertexPos[i][j];
		}
		for (unsigned short j = 2; j < 4; j++)
		{
			vertices[i][j] = uvPos[i][j - 2];
		}
	}

	*vBuffer = Singleton::GetRenderer()->GetNewVertexBuffer(vertices, 4 * (sizeof(float) * 2 + sizeof(float) * 2));
	*iBuffer = Singleton::GetRenderer()->GetNewIndexBuffer(indices, 6);

	Singleton::GetRenderer()->BindSprite(0, rendererID);
	Singleton::GetRenderer()->SetSprite(rendererID);
}

Sprite::Sprite(const std::string& path, int imgSize[2],
							int spriteQuantity, int spriteNumber)
{
	rendererID = 0;
	filePath = path;
	width = imgSize[0];
	height = imgSize[1];
	bitsPerPixel = 0;

	Singleton::GetRenderer()->GetNewSprite(path, &width, &height, &bitsPerPixel, &rendererID);

	float widthHeightRatio = width / height;
	float adjustedX = 0.5f * widthHeightRatio;

	float vertexPos[4][2] =
	{
		{-adjustedX, -1},
		{adjustedX, -1},
		{adjustedX, 1},
		{-adjustedX, 1}
	};
	
	float leftX = (float)spriteNumber / spriteQuantity;
	float rightX = (float)(spriteNumber+1) / spriteQuantity;

	float uvPos[4][2] =
	{
		{leftX, 0}, //bot left
		{rightX, 0}, //bot right
		{rightX, 1}, //top right
		{leftX, 1}  //top left
	};
	unsigned int indices[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	for (unsigned short i = 0; i < 4; i++)
	{
		for (unsigned short j = 0; j < 2; j++)
		{
			vertices[i][j] = vertexPos[i][j];
		}
		for (unsigned short j = 2; j < 4; j++)
		{
			vertices[i][j] = uvPos[i][j - 2];
		}
	}

	*vBuffer = Singleton::GetRenderer()->GetNewVertexBuffer(vertices, 4 * (sizeof(float) * 2 + sizeof(float) * 2));
	*iBuffer = Singleton::GetRenderer()->GetNewIndexBuffer(indices, 6);

	Singleton::GetRenderer()->BindSprite(0, rendererID);
	Singleton::GetRenderer()->SetSprite(rendererID);
}

Sprite::Sprite(unsigned int bufferID, int imgSize[2], int spriteQuantity, int spriteNumber)
{
	rendererID = 0;
	*vBuffer = bufferID;
	bitsPerPixel = 0;

	float widthHeightRatio = width / height;
	float adjustedX = 0.5f * widthHeightRatio;

	float vertexPos[4][2] =
	{
		{-adjustedX, -1},
		{adjustedX, -1},
		{adjustedX, 1},
		{-adjustedX, 1}
	};

	float leftX = (float)spriteNumber / spriteQuantity;
	float rightX = (float)(spriteNumber + 1) / spriteQuantity;

	float uvPos[4][2] =
	{
		{leftX, 0}, //bot left
		{rightX, 0}, //bot right
		{rightX, 1}, //top right
		{leftX, 1}  //top left
	};
	unsigned int indices[6] =
	{
		0, 1, 2,
		2, 3, 0
	};

	for (unsigned short i = 0; i < 4; i++)
	{
		for (unsigned short j = 0; j < 2; j++)
		{
			vertices[i][j] = vertexPos[i][j];
		}
		for (unsigned short j = 2; j < 4; j++)
		{
			vertices[i][j] = uvPos[i][j - 2];
		}
	}

	Singleton::GetRenderer()->SetVertexBuffer(*vBuffer, vertices, 4 * (sizeof(float) * 2 + sizeof(float) * 2));
	//Singleton::GetRenderer()->SetNewIndexBuffer(indices, 6);

	Singleton::GetRenderer()->BindSprite(0, rendererID);
	Singleton::GetRenderer()->SetSprite(rendererID);
}

Sprite::~Sprite()
{
	Singleton::GetRenderer()->DeleteSprite(&rendererID);
}

void Sprite::ChangeSprite(int spriteQuantity, int spriteNumber)
{
	float widthHeightRatio = width / height;
	float adjustedX = 0.5f * widthHeightRatio;

	float vertexPos[4][2] =
	{
		{-adjustedX, -1},
		{adjustedX, -1},
		{adjustedX, 1},
		{-adjustedX, 1}
	};

	float leftX = (float)spriteNumber / spriteQuantity;
	float rightX = (float)(spriteNumber + 1) / spriteQuantity;

	float uvPos[4][2] =
	{
		{leftX, 0}, //bot left
		{rightX, 0}, //bot right
		{rightX, 1}, //top right
		{leftX, 1}  //top left
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

	Singleton::GetRenderer()->SetVertexBuffer(*vBuffer, tempVertices, 4 * (sizeof(float) * 2 + sizeof(float) * 2));
	//Singleton::GetRenderer()->SetNewIndexBuffer(indices, 6);

	Singleton::GetRenderer()->BindSprite(0, rendererID);
	Singleton::GetRenderer()->SetSprite(rendererID);
}

void Sprite::SetAnim(Animation* _anim)
{
	anim = _anim;
}

void Sprite::UpdateFrame()
{
	anim->Update();

	//Also update U
	Vector2 uCoords = anim->GetCurrentFrame();
	
	ChangeSprite(uCoords.x, uCoords.y);
}

void Sprite::ChangeSprite(float leftU, float rightU)
{
	float uvPos[4][2] =
	{
		{leftU, 0}, //bot left
		{rightU, 0}, //bot right
		{rightU, 1}, //top right
		{leftU, 1}  //top left
	};

	//ONLY CHANGES TEX COORD FROM EACH VERTEX
	for (unsigned short i = 0; i < 4; i++)
	{
		for (unsigned short j = 2; j < 4; j++)
		{
			vertices[i][j] = uvPos[i][j - 2];
		}
	}

	Singleton::GetRenderer()->SetVertexBuffer(*vBuffer, vertices, 4 * (sizeof(float) * 2 + sizeof(float) * 2));

	Singleton::GetRenderer()->BindSprite(0, rendererID);
	Singleton::GetRenderer()->SetSprite(rendererID);
}

void Sprite::Bind()
{
	Singleton::GetRenderer()->BindSprite(0, rendererID);
	Singleton::GetRenderer()->SetSprite(rendererID);
}

void Sprite::UnBind()
{
	Singleton::GetRenderer()->UnbindSprite();
}

void Sprite::Draw()
{
	Bind();
	Singleton::GetRenderer()->Draw(*vBuffer, *iBuffer, modelID);
}