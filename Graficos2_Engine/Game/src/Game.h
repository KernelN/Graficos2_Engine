#pragma once

#include "..\..\Engine\src\Base.h"
#include "..\..\Engine\src\Entity\Entity2D\Shape\Shapes\Square.h"
#include "..\..\Engine\src\Entity\Entity2D\Shape\Shapes\Triangle.h"
#include "..\..\Engine\src\Entity\Entity2D\Sprite\Sprite.h"
#include "..\..\Engine\src\Entity\Entity3D\Cube\Cube.h"

class Game : protected BaseEngine
{
public:
	Game();
	~Game();
	bool IsRunning();
	void Loop();
	void OnLoop() override;
	void Draw() override;
	void MoveCamera();
	void MovePlayer();
private:
	Camera* camera;
	Entity3D* player;
	Entity3D* enemy;

	int scaleMod;
	int verticalMoveMod;
	int horizontalMoveMod;


};