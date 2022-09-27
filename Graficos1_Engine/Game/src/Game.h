#pragma once

#include "..\..\Engine\src\Base.h"
#include "..\..\Engine\src\Entity\Entity2D\Shape\Shapes\Square.h"

class Game : public BaseEngine
{
public:
	Game();
	~Game();
	bool IsRunning();
	void Loop();
	void Draw() override;

private:
	Square* square;



};
