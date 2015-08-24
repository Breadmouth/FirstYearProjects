#include "Mat3.h"
#include <cmath>

//constructors
Mat3::Mat3()
{
	m1 = 1;
	m2 = 0;
	m3 = 0;
	m4 = 0;
	m5 = 1;
	m6 = 0;
	m7 = 0;
	m8 = 0;
	m9 = 1;
}

Mat3::Mat3( float a_m1, float a_m2, float a_m3,  
			float a_m4, float a_m5, float a_m6,
			float a_m7, float a_m8, float a_m9 )
{
	m1 = a_m1;
	m2 = a_m2;
	m3 = a_m3;
	m4 = a_m4;
	m5 = a_m5;
	m6 = a_m6;
	m7 = a_m7;
	m8 = a_m8;
	m9 = a_m9;
}

//create
//
Mat3 Mat3::CreateTranslation(Vector3 rhs)
{
	m1 = 1;
	m2 = 0;
	m3 = 0;
	m4 = 0;
	m5 = 1;
	m6 = 0;
	m7 = rhs.x;
	m8 = rhs.y;
	m9 = 1;
	return *this;
}

void Mat3::CreateScale(float sx, float sy)
{
	m1 = sx; 
	m2 = 0;
	m3 = 0;
	m4 = 0;
	m5 = sy;
	m6 = 0;
	m7 = 0;
	m8 = 0;
	m9 = 1;
}

Mat3 Mat3::CreateScale(Vector3 rhs)
{
	m1 = rhs.x;
	m2 = 0;
	m3 = 0;
	m4 = 0;
	m5 = rhs.y;
	m6 = 0;
	m7 = 0;
	m8 = 0;
	m9 = 1;
	return *this;
}

Mat3 Mat3::CreateRotation(float rot)
{
	m1 = cos(rot); 
	m2 = -sin(rot);
	m3 = 0;
	m4 = sin(rot);
	m5 = cos(rot);
	m6 = 0;
	m7 = 0;
	m8 = 0;
	m9 = 1;
	return *this;

}

//translate
//
Vector2 Mat3::GetTranslation()
{
	return Vector2(m7, m8);
}

void Mat3::Translate(float tx, float ty)
{
	m7 += tx;
	m8 += ty;
}

void Mat3::Translate(Vector2 vec)
{
	m7 += vec.x;
	m8 += vec.y;
}

void Mat3::SetTranslation(float tx, float ty)
{
	m7 = tx;
	m8 = ty;
}

void Mat3::SetTranslation(Vector2 vec)
{
	m7 = vec.x;
	m8 = vec.y;
}


//scale
//
Vector2 Mat3::GetScale()
{
	return Vector2(sqrt(pow(m1, 2) + pow(m2, 2)) , sqrt(pow(m4, 2) + pow(m5, 2)));
}

void Mat3::SetScale(float x, float y)
{
	m1 = x;
	m5 = y;
}


//rotate
//
void Mat3::SetRotation(float rad)
{

}

void Mat3::SetUpRotation(float rad)
{
	m3 = cos(rad);
	m4 = sin(rad);
}

void Mat3::SetRightRotation(float rad)
{
	m1 = cos(rad);
	m2 = sin(rad);
}

float Mat3::GetUpRotation()
{
	Vector2 up = Vector2 (0, 1);
	return up.AngleBetween(Vector2(m3, m4));

}

float Mat3::GetRightRotation()
{
	Vector2 right = Vector2 (1, 0);
	return right.AngleBetween(Vector2(m1, m2));
}

float Mat3::GetRotation()
{
	return atan2f(m4, m5);
}

//operators
//
Mat3 Mat3::operator * (const Mat3 &rhs) const
{
	Mat3 temp;
	temp.m1 = (m1 * rhs.m1) + (m2 * rhs.m4) + (m3 * rhs.m7);
	temp.m2 = (m1 * rhs.m2) + (m2 * rhs.m5) + (m3 * rhs.m8);
	temp.m3 = (m1 * rhs.m3) + (m2 * rhs.m6) + (m3 * rhs.m9);

	temp.m4 = (m4 * rhs.m1) + (m5 * rhs.m4) + (m6 * rhs.m7);
	temp.m5 = (m4 * rhs.m2) + (m5 * rhs.m5) + (m6 * rhs.m8);
	temp.m6 = (m4 * rhs.m3) + (m5 * rhs.m6) + (m6 * rhs.m9);

	temp.m7 = (m7 * rhs.m1) + (m8 * rhs.m4) + (m9 * rhs.m7);
	temp.m8 = (m7 * rhs.m2) + (m8 * rhs.m5) + (m9 * rhs.m8);
	temp.m9 = (m7 * rhs.m3) + (m8 * rhs.m6) + (m9 * rhs.m9);

	return temp;
}

Mat3& Mat3::operator *= (const Mat3 &rhs)
{
	*this = *this * rhs;
	return *this;
}

Mat3& Mat3::operator = (const Mat3 &rhs)
{
	m1 = rhs.m1;
	m2 = rhs.m2;
	m3 = rhs.m3; 
	m4 = rhs.m4; 
	m5 = rhs.m5; 
	m6 = rhs.m6;
	m7 = rhs.m7;
	m8 = rhs.m8;
	m9 = rhs.m9;
	return *this;
}

Vector3 Mat3::operator * (const Vector3 &rhs) const
{
	Vector3 temp;
	temp.x = (rhs.x * m1) + (rhs.y * m4) + (rhs.z * m7);
	temp.y = (rhs.x * m2) + (rhs.y * m5) + (rhs.z * m8);
	temp.z = (rhs.x * m3) + (rhs.y * m6) + (rhs.z * m9);

	return temp;
}

Mat3 Mat3::operator / (const float rhs)	const
{
	return Mat3(m1 / rhs, m2 / rhs, m3 / rhs, m4 / rhs, m5 / rhs, m6 / rhs, m7 / rhs, m8 / rhs, m9 / rhs);
}

float Mat3::Det()
{
	return (((m1 * m5 * m9) + (m2 * m6 * m7) + (m3 * m4 * m8)) - ((m3 * m5 * m7) + (m2 * m4 * m9) + (m1 * m6 * m8)));
}

Mat3 Mat3::Transpose()
{
	return Mat3(m1, m4, m7, m2, m5, m8, m3, m6, m9);
}

Mat3 Mat3::Adjugate()
{
	Mat3 m_adjugate = Mat3(	+((m5 * m9) - (m6 * m8)), -((m4 * m9) - (m6 * m7)), +((m4 * m8) - (m5 * m7)),
							-((m2 * m9) - (m3 * m8)), +((m1 * m9) - (m3 * m7)), -((m1 * m8) - (m2 * m7)), 
							+((m2 * m6) - (m3 * m5)), -((m1 * m6) - (m3 * m4)), +((m1 * m5) - (m2 * m4)));
	m_adjugate = m_adjugate.Transpose();
	return m_adjugate;
}

Mat3 Mat3::Inverse()
{
	return Mat3( Adjugate() / Det());
}