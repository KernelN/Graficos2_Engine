#pragma once
#include<vector>
#include "Entity/Entity2D/Sprite/Sprite.h"

class Animation
{
public:
	Animation(std::string animPath, unsigned int spriteQty);
	~Animation();
	void ChangeSprite(int spriteNumber);

private:
	std::vector<Sprite*> sprites;
	float timer;
};