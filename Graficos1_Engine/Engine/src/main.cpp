#include <Base.h>

int main()
{
	Base* base = new Base();
	base->DoFunnyStuff();
	delete base;
	return 0;
}