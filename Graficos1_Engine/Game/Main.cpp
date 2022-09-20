#include "../Engine/src/Base.h"



int main()
{
	Base* base = new Base();

	while (base->IsRunning())
	{
		base->Loop();
	}

	delete base;

}