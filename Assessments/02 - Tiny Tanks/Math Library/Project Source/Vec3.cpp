#include "Vec3.h"
#include <iostream>
#include <cmath>

#define PI 3.1415

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 1;

}

Vector3::Vector3( float a_x, float a_y)
{
	x = a_x;
	y = a_y;
	z = 1;
}

Vector3::Vector3(Vector2 rhs)
{
	x = rhs.x;
	y = rhs.y;
	z = 1;
}

Vector3 Vector3::operator * (float rhs)		const
{
	return Vector3( x * rhs, y * rhs);
}

void Vector3::operator *= (float rhs)
{
	x = x * rhs;
	y = y * rhs;
}

void Vector3::operator = (Vector3 rhs)
{
	x = rhs.x;
	y = rhs.y;
}

Vector3 Vector3::operator - (const Vector3 rhs)		const
{
	return Vector3(x - rhs.x, y - rhs.y);
}

float Vector3::GetLength()	const
{
	if (sqrt((x * x) + (y * y)) != 0)
		return sqrt((x * x) + (y * y));
	else return 0.000001f;
}

void Vector3::Normalise()
{
	float temp = GetLength();
	x = x / temp;
	y = y / temp;
}

float Vector3::Dot(const Vector3 &rhs)	const
{
	//normalise values
	Vector3 temp1(0, -1);

	return ((temp1.x * rhs.x) + (temp1.y * rhs.y));
}

float Vector3::AngleBetween(Vector3 rhs)	const
{ 
	Vector3 perp = Vector3(rhs.y, -rhs.x);
	float len1 = GetLength();
	float len2 = rhs.GetLength();

	float angle = acos(Dot(rhs));

	if (rhs.Dot(perp) > 0)
		return angle;
	else return -angle;
}