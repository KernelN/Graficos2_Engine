#pragma once
#include<vector>
#include "Entity/Entity2D/Sprite/Sprite.h"

class Animation
{
public:
	Animation(float animLength, unsigned int framesQty);
	~Animation();
	void Update();
	void AddFrame(Vector2 _uCoords);
	Vector2 GetCurrentFrame();
	Vector2 GetFrame(int frame);

private:
	std::vector<Vector2> uCoords; //use only left U and right U
	float timer;
	float length;
	int currentFrame;
};