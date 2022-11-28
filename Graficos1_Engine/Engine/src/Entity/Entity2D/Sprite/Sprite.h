#pragma once
#include "Entity/Entity2D/Entity2D.h"
#include <string>
#include "DLLManager.h"
#include "Animation/Animation.h"


class DLLEXPORT Sprite : public Entity2D
{
private:
	unsigned int rendererID;
	std::string filePath;
	int width, height, bitsPerPixel;
	float vertices[4][4];
	Animation* anim;

	void ChangeSprite(float leftU, float rightU);

public:
	Sprite(const std::string& path);
	Sprite(const std::string& path, int imgSize[2]);
	Sprite(const std::string& path, int imgSize[2], int spriteQuantity, int spriteNumber);
	Sprite(unsigned int bufferID, int imgSize[2], int spriteQuantity, int spriteNumber);
	~Sprite();

	void ChangeSprite(int spriteQuantity, int spriteNumber);
	void SetAnim(Animation* _anim);
	void UpdateFrame();
	void Bind();
	void UnBind();
	void Draw();
	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }
};