#pragma once

///	\brief	A Vector2 class that contains 2 variables to represent the x and y data
///			and various functions to handle operations to the those variables

class Vector2
{
public:

	///create vector2 with x and y members set to 0
	///
	Vector2();

	///create vector2 setting x and y to user input data
	///@param a_x the x data to put in the Vector2
	///@param a_y the y data to put in the Vector2
	Vector2(float a_x, float a_y);

	///overloaded + operator to allow Vector2 + Vector2
	///@param rhs contains the Vector2 to operate on
	///@return Vector2 the result of the operation
	Vector2 operator + (Vector2 rhs)		const;

	///overloaded - operator to allow Vector2 - Vector2
	///@param rhs contains the Vector2 to operate on
	///@return Vector2 the result of the operation
	Vector2 operator - (Vector2 rhs)		const;

	///overloaded * operator to allow Vector2 * float
	///@param rhs contains the float to operate on
	///@return Vector2 the result of the operation
	Vector2 operator * (float rhs)			const;

	///overloaded / operator to allow Vector2 / float
	///@param rhs contains the float to operate on
	///@return Vector2 the result of the operation
	Vector2 operator / (float rhs)			const;

	Vector2 operator / (Vector2 rhs)		const;

	///overloaded += operator to allow Vector2 += vector2
	///@param rhs contains the Vector2 to operate on
	///@return void
	void operator += (Vector2 rhs);

	///overloaded -= operator to allow Vector2 / Vector2
	///@param rhs contains the Vector2 to operate on
	///@return void
	void operator -= (Vector2 rhs);

	///overloaded *= operator to allow Vector2 / float
	///@param rhs contains the float to operate on
	///@return void
	void operator *= (float rhs);

	///overloaded /= operator to allow Vector2 / float
	///@param rhs contains the float to operate on
	///@return void
	void operator /= (float rhs);

	///overloaded = operator to allow Vector2 = Vector2
	///@param rhs contains the Vector2 to operate on
	///@return void
	void operator = (Vector2 rhs);

	bool operator == (Vector2 rhs);

	///returns the length of the Vector2
	///@return float the length of the Vector2
	float GetLength()						const;

	///Normalises the Vector2
	///@return void
	void Normalise();							

	///perform dot operation between two Vector2s
	///@param rhs contains the Vector2 to perform the dot operation on
	///@return float the result of the dot operation
	float Dot(const Vector2 rhs)			const;

	///return the angle between two Vector2s
	///@param rhs contains the Vector2 to perform the angle between operation on
	///@return float the result of the angle between operation
	float AngleBetween(const Vector2 rhs)	const;

	///Vector2 x component
	float x;

	///vector2 y component
	float y;

private:
	
};