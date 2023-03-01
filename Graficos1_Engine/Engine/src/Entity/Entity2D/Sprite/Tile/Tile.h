#pragma once
#include "DLLManager.h"
#include "Entity/Entity2D/Sprite/Sprite.h"

class DLLEXPORT Tile : public Sprite
{
public:
	Tile();
	~Tile();

	bool isWalkable();
	void walkability(bool bWalkable);

	unsigned int getId();
	void setId(unsigned int id);

private:
	unsigned int _id;
	bool _walkable;
};