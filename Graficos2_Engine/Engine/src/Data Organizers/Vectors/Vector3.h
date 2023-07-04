#pragma once

#include <cmath>

#include "DLLManager.h"

struct DLLEXPORT Vector3
{
public:	
	float x;
	float y;
	float z;

#pragma region operators
	Vector3 operator+(const Vector3& other) const
	{
		Vector3 vec;
		vec.x = x + other.x;
		vec.y = y + other.y;
		vec.z = z + other.z;
		return vec;
	}
	Vector3 operator-(const Vector3& other) const
	{
		Vector3 vec;
		vec.x = x - other.x;
		vec.y = y - other.y;
		vec.z = z - other.z;
		return vec;
	}
	Vector3 operator*(const float& other) const
	{
		Vector3 vec;
		vec.x = x * other;
		vec.y = y * other;
		vec.z = z * other;
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
# pragma endregion

	float GetSqrMagnitude()
	{
		return x * x + y * y + z * z;
	}
	float GetMagnitude()
	{
		return sqrt(GetSqrMagnitude());
	}
};

const static Vector3 zero = Vector3{ 0, 0, 0 };