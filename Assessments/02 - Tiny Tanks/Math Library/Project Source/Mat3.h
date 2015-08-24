#pragma once

#include "Vec2.h"
#include "Vec3.h"

///	\brief	A 3 * 3 Matrix class that contains 9 variables to represent the matrix data
///			and various functions to handle operations to the matrix data

class Mat3
{
public:
	///	sets default data to identity matrix
	///	
	Mat3();


	///	creates a 3x3 matrix using user input data
	///	
	Mat3(	float a_m1, float a_m2, float a_m3,  
			float a_m4, float a_m5, float a_m6,
			float a_m7, float a_m8, float a_m9 );		

	///create a 3x3 matrix with vector3 translation information
	///@param rhs contains the x and y to be converted to a translation matrix
	///@return Mat3 the new translation matrix
	Mat3 CreateTranslation(Vector3 rhs);

	///create a 3x3 matrix with vector3 scale information
	///@param rhs contains the x and y to be converted to a scale matrix
	///@return Mat3 the new scale matrix
	Mat3 CreateScale(Vector3 rhs);

	///create a 3x3 matrix with x and y scale information
	///@param sx contains the x to be converted to a scale matrix
	///@param sy contains the y to be converted to a scale matrix
	///@return void
	void CreateScale(float sx, float sy);	

	///create a 3x3 matrix with radian rotation information
	///@param rot conatains the radians to be converted to a rotation matrix
	///@return Mat3 the new rotation matrix
	Mat3 CreateRotation(float rot);

	///return matrix translation as a vector2
	///@return Vector2 the matrix's current translation
	Vector2 GetTranslation();		

	///translate matrix by x and y
	///@param tx contains the x to translate the matrix
	///@param ty contains the y to translate the matrix
	///@return void
	void Translate(float tx, float ty);

	///translate matrix by vector2
	///@param vec contains the x and y to translate the matrix
	///@return void
	void Translate(Vector2 vec);

	///set matrix translation with x and y
	///@param tx contains the x to set the matrix's current tanslation
	///@param ty contains the y to set the matrix's current tanslation
	///@return void
	void SetTranslation(float tx, float ty);

	///set matrix translation with vector2
	///@param vec contains the x and y to set the matrix's current tanslation
	///@return void
	void SetTranslation(Vector2 vec);		

	///return matrix scale as vector2
	///@return Vector2 the matrix's current scale
	Vector2 GetScale();			

	///set matrix scale with x and y
	///@param x contains the x to set the matrix's current scale
	///@param y contains the y to set the matrix's current scale
	///@return void
	void SetScale(float x, float y);		

	///set matrix rotation with radians
	///@param rad contains the radians to set the matrix's current rotation
	///@return void
	void SetRotation(float rad);			

	///set up rotation with radians
	///@param rad contains the radians to set the matrix's current up rotation
	///@return void
	void SetUpRotation(float rad);	

	///set right rotation with radians
	///@param rad contains the radians to set the matrix's current right rotation
	///@return void
	void SetRightRotation(float rad);		

	///return up rotation in radians
	///@return float the matrix's current up rotation
	float GetUpRotation();

	///return right rotation in radians
	///@return float the matrix's current right rotation
	float GetRightRotation();

	///return matrix rotation in radians
	///@return float the matrix's current rotation
	float GetRotation();					

	///overloaded * operator to perform Mat3 * Mat3
	///@param &rhs contains a pointer to the Mat3 to operate on
	///@return Mat3 the result of the operation
	Mat3 operator * (const Mat3 &rhs)	const;

	///overloaded / operator to perform Mat3 / float
	///@param &rhs contains a pointer to the float to operate on
	///@return Mat3 the result of the operation
	Mat3 operator / (const float rhs)	const;

	///overloaded *= operator to perform Mat3 *= Mat3
	///@param &rhs contains a pointer to the Mat3 to operate on
	///@return Mat3 the result of the operation
	Mat3& operator *= (const Mat3 &rhs);

	///overloaded = operator to perform Mat3 = Mat3
	///@param &rhs contains a pointer to the Mat3 to operate on
	///@return Mat3 the result of the operation
	Mat3& operator = (const Mat3 &rhs);

	///overloaded * operator to perform Mat3 * Vector3
	///@param &rhs contains a pointer to the Vector3 to operate on
	///@return Mat3 the result of the operation
	Vector3 operator * (const Vector3 &rhs) const;

	///Return the inverse of the Matrix
	///@return Mat3 the inverse of the matrix
	Mat3 Inverse();

protected:

	///return matrix determinant
	///@return float the determinant of the matrix
	float Det();	

	///transpose the matrix
	///@return Mat3 the transposed matrix
	Mat3 Transpose();			

	///return the matrix adjugate
	///@return Mat3 the adjugate matrix
	Mat3 Adjugate();						

		///column 1, row 1
	float	m1,
		///column 2, row 1
			m2, 
		///column 3, row 1
			m3,
		///column 1, row 2
			m4,
		///column 2, row 2
			m5,
		///column 3, row 2
			m6,
		///column 1, row 3
			m7, 
		///column 2, row 3
			m8, 
		///column 3, row 3
			m9;





};