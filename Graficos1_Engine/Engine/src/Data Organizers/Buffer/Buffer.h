#pragma once
#include "DLLManager.h"

class DLLEXPORT Buffer
{
public:
	Buffer();
	~Buffer();
protected:
	unsigned int* buffer;
	unsigned int ammount;
};