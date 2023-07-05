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
		// Vector3 vec;
		// vec.x = x + other.x;
		// vec.y = y + other.y;
		// vec.z = z + other.z;
		return {x + other.x, y + other.y, z + other.z};
	}
	Vector3 operator-(const Vector3& other) const
	{
		// Vector3 vec;
		// vec.x = x - other.x;
		// vec.y = y - other.y;
		// vec.z = z - other.z;
		return { x - other.x, y - other.y, z - other.z };
	}
	Vector3 operator*(const float& other) const
	{
		// Vector3 vec;
		// vec.x = x * other;
		// vec.y = y * other;
		// vec.z = z * other;
		return {x * other, y * other, z * other};
	}
	void operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
	}
# pragma endregion

	float GetSqrMagnitude() const
	{
		return x * x + y * y + z * z;
	}
	float GetMagnitude() const
	{
		return sqrt(GetSqrMagnitude());
	}
};

const static Vector3 zero = Vector3{ 0, 0, 0 };