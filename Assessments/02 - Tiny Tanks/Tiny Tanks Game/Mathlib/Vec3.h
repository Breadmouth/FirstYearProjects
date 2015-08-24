#pragma once
#include "Vec2.h"

///	\brief	A Vector3 class that contains 3 variables to represent the x, y, and z data
///			and various functions to handle operations to the those variables

class Vector3
{
public:

	///create vector3 with x, y and z members set to 0
	///
	Vector3();

	///create vector3 setting x and y to user input data
	///@param a_x the x data to put in the Vector3
	///@param a_y the y data to put in the Vector3
	Vector3(float a_x, float a_y);

	///create vector3 setting x and y to user input data
	///@param rhs the x and y data to put in the Vector3
	Vector3(Vector2 rhs);

	///overloaded * operator to allow Vector3 * float
	///@param rhs contains the float to operate on
	///@return Vector3 the result of the operation
	Vector3 operator * (const float rhs)		const;

	///overloaded *= operator to allow Vector3 / float
	///@param rhs contains the float to operate on
	///@return void
	void operator *= (float rhs);

	///overloaded = operator to allow Vector3 = Vector3
	///@param rhs contains the Vector3 to operate on
	///@return void
	void operator = (Vector3 rhs);

	///overloaded - operator to allow Vector3 - Vector3
	///@param rhs contains the Vector3 to operate on
	///@return Vector3 the result of the operation
	Vector3 operator - (const Vector3 rhs)		const;

	///returns the length of the Vector3
	///@return float the length of the Vector3
	float GetLength()						const;

	///Normalises the Vector3
	///@return void
	void Normalise();							

	///perform dot operation between two Vector3s
	///@param rhs contains the Vector3 to perform the dot operation on
	///@return float the result of the dot operation
	float Dot(const Vector3 &rhs)			const;	

	///return the angle between two Vector3s
	///@param rhs contains the Vector3 to perform the angle between operation on
	///@return float the result of the angle between operation
	float AngleBetween(const Vector3 rhs)	const;	

	///Vector2 x component
	float x;	

	///Vector2 y component
	float y;	

	///Vector2 z component
	float z;	

private:
	
};