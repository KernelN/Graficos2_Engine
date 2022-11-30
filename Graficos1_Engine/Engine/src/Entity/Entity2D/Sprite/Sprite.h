#pragma once
#include "Entity/Entity2D/Entity2D.h"
#include <string>
#include "DLLManager.h"
#include "Animation/Animation.h"


class DLLEXPORT Sprite : public Entity2D
{
private:
	unsigned int rendererID;
	unsigned int imageID;
	std::string filePath;
	int width, height, bitsPerPixel;
	float vertices[4][4];
	Animation* anim;
	unsigned int spriteQty;

	void ChangeSprite(float leftU, float rightU);
	void Bind();
	void UnBind();

public:
	Sprite(const std::string& path);
	Sprite(const std::string& path, int imgSize[2]);
	Sprite(const std::string& path, int imgSize[2], int spriteQuantity, int spriteNumber);
	Sprite(unsigned int _imageID, int imgSize[2], int spriteQuantity, int spriteNumber);
	~Sprite();

	void ChangeSprite(int spriteQuantity, int spriteNumber);
	void SetAnim(Animation* _anim);
	void UpdateFrame();
	void Draw();
	unsigned int GetImageID();
	inline int GetWidth() const { return width; }
	inline int GetSpriteQty() const { return spriteQty; }
	inline int GetHeight() const { return height; }
};