#include "Animation.h"
#include "Utility/Singleton.h"

Animation::Animation(float animLength = 0, unsigned int framesQty = 0)
{

}

Animation::~Animation()
{
}

void Animation::Update()
{
	
}

void Animation::AddFrame(Vector2 _uCoords)
{
	uCoords.push_back(_uCoords);
}

Vector2 Animation::GetCurrentFrame()
{
	return uCoords[currentFrame];
}

Vector2 Animation::GetFrame(int frame)
{
	return uCoords[frame];
}