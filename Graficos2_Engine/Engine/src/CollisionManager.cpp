#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

//https://tutorialedge.net/gamedev/aabb-collision-detection-tutorial/ Inspired by tutorial
bool CollisionManager::CheckCollision(Entity2D* entity1, Entity2D* entity2)
{
	int x1 = entity1->GetTranslation().x;
	int y1 = entity1->GetTranslation().y;
	int x2 = entity2->GetTranslation().x;
	int y2 = entity2->GetTranslation().y;

	int xHalf1 = entity1->GetScale().x / 2;
	int yHalf1 = entity1->GetScale().y / 2;

	int xHalf2 = entity2->GetScale().x / 2;
	int yHalf2 = entity2->GetScale().y / 2;

	bool right1Collision = x1 + xHalf1 > x2 - xHalf2;
	bool left1Collision = x1 - xHalf1 < x2 + xHalf2;
	bool top1Collision = y1 + yHalf1 > y2 - yHalf2;
	bool bot1Collision = y1 - yHalf1 < y2 + yHalf2;

	bool collision = right1Collision && left1Collision && top1Collision && bot1Collision;

	return collision;
}