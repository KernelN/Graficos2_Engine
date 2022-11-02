#pragma once
#include<vector>
#include "Entity/Entity2D/Sprite/Sprite.h"

class Animation
{
public:
	Animation(Sprite* _sprites[], unsigned int spriteQty);
	~Animation();

private:
	std::vector<Sprite*> sprites;
	float timer;
};