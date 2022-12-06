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

	//int width1 = entity1->GetScale().x;
	//int height1 = entity1->GetScale().y;

	//int width2 = entity2->GetScale().x;
	//int height2 = entity2->GetScale().y;

	int width1 = entity1->GetScale().x / 2;
	int height1 = entity1->GetScale().y / 2;

	int width2 = entity2->GetScale().x / 2;
	int height2 = entity2->GetScale().y / 2;

	//bool right1Collision = x1 < x2 + width2;
	//bool left1Collision = x1 + width1 > x2;
	//bool top1Collision = y1 < y2 + height2;
	//bool bot1Collision = y1 + height1 > y2;

	//CLAVE
	bool right1Collision = x1 + width1 > x2 - width2;
	bool left1Collision = x1 - width1 < x2 + width2;
	bool top1Collision = y1 + height1 > y2 - height2;
	bool bot1Collision = y1 - height1 < y2 + height2;

	//CLAVE
	bool collision = right1Collision && left1Collision && top1Collision && bot1Collision;

	//bool collision = (right1Collision || left1Collision) && (top1Collision || bot1Collision);
	//bool collision = x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2;

	return collision;

	//return x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2;
}

bool CollisionManager::CheckCollision(Sprite* sprite1, Sprite* sprite2)
{
	int x1 = sprite1->GetTranslation().x;
	int y1 = sprite1->GetTranslation().y;
	int x2 = sprite2->GetTranslation().x;
	int y2 = sprite2->GetTranslation().y;

	//int width1 = sprite1->GetWidth() + sprite1->GetScale().x;
	//int height1 = sprite1->GetHeight() + sprite1->GetScale().y;

	//int width2 = sprite2->GetWidth() + sprite2->GetScale().x;
	//int height2 = sprite2->GetHeight() + sprite2->GetScale().y;

	int width1 = sprite1->GetWidth() / 2 + sprite1->GetScale().x / 2;
	int height1 = sprite1->GetHeight() / 2 + sprite1->GetScale().y / 2;

	int width2 = sprite2->GetWidth() / 2 + sprite2->GetScale().x / 2;
	int height2 = sprite2->GetHeight() / 2 + sprite2->GetScale().y / 2;

	//int width1 = ((sprite1->GetWidth() / 6) * sprite1->GetScale().x) / 2;
	//int height1 = (sprite1->GetHeight() * sprite1->GetScale().y) / 2;

	//int width2 = ((sprite2->GetWidth() / 6) * sprite2->GetScale().x) / 2;
	//int height2 = (sprite2->GetHeight() / sprite2->GetScale().y) / 2;

	bool right1Collision = x1 < x2 + width2;
	bool left1Collision = x1 + width1 > x2;
	bool top1Collision = y1 < y2 + height2;
	bool bot1Collision = y1 + height1 > y2;

	//CLAVE
	//bool right1Collision = x1 + width1 > x2 - width2;
	//bool left1Collision = x1 - width1 < x2 + width2;
	//bool top1Collision = y1 + height1 > y2 - height2;
	//bool bot1Collision = y1 - height1 < y2 + height2;

	//CLAVE
	bool collision = right1Collision && left1Collision && top1Collision && bot1Collision;

	//bool collision = (right1Collision || left1Collision) && (top1Collision || bot1Collision);
	//bool collision = x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2;

	return collision;

	//return x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2;
}
