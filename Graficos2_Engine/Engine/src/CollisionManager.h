#pragma once
#include "Entity/Entity2D/Entity2D.h"
#include "Entity/Entity2D/Sprite/Sprite.h"
#include "DLLManager.h"

class DLLEXPORT CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	bool CheckCollision(Entity2D* entity1, Entity2D* entity2);
	bool CheckCollision(Sprite* entity1, Sprite* entity2);
};



