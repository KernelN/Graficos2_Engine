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
	Entity2D* player;
	Entity2D* enemy;

	int scaleMod;
	int verticalMoveMod;
	int horizontalMoveMod;


};