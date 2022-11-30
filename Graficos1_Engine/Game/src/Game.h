#pragma once

#include "..\..\Engine\src\Base.h"
#include "..\..\Engine\src\Entity\Entity2D\Shape\Shapes\Square.h"
#include "..\..\Engine\src\Entity\Entity2D\Shape\Shapes\Triangle.h"
#include "..\..\Engine\src\Entity\Entity2D\Sprite\Sprite.h"

class Game : protected BaseEngine
{
public:
	Game();
	~Game();
	bool IsRunning();
	void Loop();
	void OnLoop() override;
	void Draw() override;

private:
	Square* square;
	Triangle* triangle;
	Sprite* sprite1;
	Sprite* sprite2;
	//Sprite* sprite[4];

	int scaleMod;
	int verticalMoveMod;
	int horizontalMoveMod;


};