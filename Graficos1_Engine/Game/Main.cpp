#include "../Engine/src/Base.h"
#include "src/Game.h"


int main()
{
	Game* base = new Game();

	while (base->IsRunning())
	{
		base->Loop();
	}

	delete base;
}