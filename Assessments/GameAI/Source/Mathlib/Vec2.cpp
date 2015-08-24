#include "Vec2.h"
#include <iostream>
#include <cmath>

#define PI 3.1415

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2( float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

Vector2 Vector2::operator + (Vector2 rhs)	const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator - (Vector2 rhs)	const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator * (float rhs)		const
{
	return Vector2( x * rhs, y * rhs);
}

Vector2 Vector2::operator / (float rhs)		const
{
	return Vector2( x / rhs, y / rhs);
}

Vector2 Vector2::operator / (Vector2 rhs)	const
{
	return Vector2 ( x / rhs.x, y / rhs.y);
}

void Vector2::operator += (Vector2 rhs)
{
	x = x + rhs.x;
	y = y + rhs.y;
}

void Vector2::operator -= (Vector2 rhs)
{
	x = x - rhs.x;
	y = y - rhs.y;
}

void Vector2::operator *= (float rhs)
{
	x = x * rhs;
	y = y * rhs;
}

void Vector2::operator /= (float rhs)
{
	x = x / rhs;
	y = y / rhs;
}

void Vector2::operator = (Vector2 rhs)
{
	x = rhs.x;
	y = rhs.y;
}

bool Vector2::operator == (Vector2 rhs)
{
	if ( x == rhs.x && y == rhs.y )
		return true;
	return false;
}


float Vector2::GetLength()	const
{
	if (sqrt((x * x) + (y * y)) != 0)
		return sqrt((x * x) + (y * y));
	else return 0.0001f;
}

void Vector2::Normalise()
{
	float temp = GetLength();
	x = x / temp;
	y = y / temp;
}

float Vector2::Dot(Vector2 rhs)	const
{
	//normalise values
	Vector2 temp1(0, -1);

	return ((temp1.x * rhs.x) + (temp1.y * rhs.y));
}

float Vector2::AngleBetween(Vector2 rhs)	const
{ 
	Vector2 perp = Vector2(rhs.y, -rhs.x);
	float len1 = GetLength();
	float len2 = rhs.GetLength();

	float temp = Dot(rhs) / (len1 + len2);
	if (temp > 1)
	{
		temp = 1;
	}
	else if (temp < -1)
	{
		temp = -1;
	}
	float angle = acos(temp);

	if (rhs.Dot(perp) > 0)
		return angle;
	else return -angle;
}