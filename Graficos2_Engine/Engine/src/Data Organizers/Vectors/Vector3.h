#pragma once
#include "DLLManager.h"

struct DLLEXPORT Vector3
{
public:	
	float x;
	float y;
	float z;

	Vector3 operator+(const Vector3& other) const
	{
		Vector3 vec;
		vec.x = x + other.x;
		vec.y = y + other.y;
		vec.z = z + other.z;
		return vec;
	}
	Vector3 operator+=(const Vector3& other)
	{
		Vector3 vec;
		vec.x = x + other.x;
		vec.y = y + other.y;
		vec.z = z + other.z;
		return vec;
	}
};

const static Vector3 zero = Vector3{ 0, 0, 0 };