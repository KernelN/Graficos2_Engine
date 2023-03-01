#pragma once
#include "Entity/Entity2D/Entity2D.h"
#include "Entity/Entity2D/Sprite/Sprite.h"
#include "DLLManager.h"

static class DLLEXPORT CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	static bool CheckCollision(Entity2D* entity1, Entity2D* entity2);
};