#pragma once

#include "..\..\Engine\src\Base.h"
#include "..\..\Engine\src\Entity\Entity2D\Shape\Shapes\Square.h"
#include "..\..\Engine\src\Entity\Entity2D\Shape\Shapes\Triangle.h"

class Game : public BaseEngine
{
public:
	Game();
	~Game();
	void Init();
	bool IsRunning();
	void Loop();
	void Draw() override;

private:
	Square* square;
	Triangle* triangle;


};
