#include <Base.h>

int main()
{
	Base* base = new Base();
	while (base->IsRunning())
	{
		base->Loop();
	}
	delete base;
	return 0;
}

void Base::Draw()
{
 //do funny stuff
}