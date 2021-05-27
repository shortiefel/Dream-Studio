/* Start Header**********************************************************************************/
/*!
\file Vector.hpp
\team name
\software name
\authors
NAME							EMAIL									ROLE
Tan Wei Ling Felicia			weilingfelicia.tan@digipen.edu			PRODUCER
Goh	See Yong Denise				2001220@sit.singaporetech.edu.sg
Ow Jian Wen						jianwen123321@hotmail.com				TECHINCAL DIRECTOR
Chia Yi Da						chiayida98@gmail.com
Margaret Teo Boon See			Teo.b@digipen.edu
Wang Ao							Ao.Wang@digipen.edu
Ng Jia Yi						Jiayi.ng@digipen.edu
\date 26/04/2021
\brief

Vectors and this supports 2D and 3D vectors

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef VectorND_H
#define VectorND_H

template <typename T>
class Vector
{
public:
	T x, y, z;

	// Constructors
	Vector() : x{ T{} }, y{ T{} }, z{ T{} } {};
	Vector(T _x, T _y) : x{ _x }, y{ _y }, z{ _z } {}

	// Assignment operators
	Vector<T>& operator += (const VectorND<T>& rhs) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector<T>& operator -= (const VectorND<T>& rhs) {
		return *this += -rhs;
	}

	Vector<T>& operator *= (T rhs) {
		x *= rhs;
		y *= rhs;
		x *= rhs;
		return *this;
	}

	Vector<T>& operator /= (T rhs) {
		x /= rhs;
		y /= rhs;
		z /= rhs;
		return *this;
	}

	// Unary operators
	Vector<T> operator-() const {
		Vector tem;
		tem.x = -x;
		tem.y = -y;
		tem.z = -z;
		return tem;
	}

};


// Binary operators
template <typename T>
Vector<T> operator + (const Vector<T>& lhs, const Vector<T>& rhs) {
	Vector tem(lhs.x, lhs.y, lhs.z);
	tem += rhs;
	return tem;
}

template <typename T>
Vector<T> operator - (const Vector<T>& lhs, const Vector<T>& rhs) {
	return lhs + -rhs;
}

template <typename T>
Vector<T> operator * (const Vector<T>& lhs, T rhs) {
	Vector tem(lhs.x, lhs.y, lhs.z);
	tem *= rhs;
	return tem;
}

template <typename T>
Vector<T> operator * (T lhs, const Vector<T>& rhs) {
	return rhs * lhs;
}

template <typename T>
Vector<T> operator / (const Vector<T>& lhs, T rhs) {
	VectorND tem(lhs.x, lhs.y, lhs.z);
	tem /= rhs;
	return tem;
}





/**************************************************************************/
/*!
	In this function, pResult will be the unit vector of pVec0
 */
 /**************************************************************************/
template <typename T>
void Vec2Normalize(Vector<T>& pResult, const Vector<T>& pVec0) {
	pResult = pVec0 / Vec2Length(pVec0);
}

/**************************************************************************/
/*!
	This function returns the length of the vector pVec0
 */
 /**************************************************************************/
template <typename T>
T Vec2Length(const Vector<T>& pVec0) {
	return T(sqrt(pow(pVec0.x, 2) + pow(pVec0.y, 2)));
}

/**************************************************************************/
/*!
	This function returns the square of pVec0's length. Avoid the square root
 */
 /**************************************************************************/
template <typename T>
T Vec2SquareLength(const Vector<T>& pVec0) {
	return T(pow(pVec0.x, 2) + pow(pVec0.y, 2));
}

/**************************************************************************/
/*!
	In this function, pVec0 and pVec1 are considered as 2D points.
	The distance between these 2 2D points is returned
 */
 /**************************************************************************/
template <typename T>
T Vec2Distance(const Vector<T>& pVec0, const Vector<T>& pVec1) {
	Vector tem(pVec0);
	tem -= pVec1;
	return Vec2Length(tem);
}

/**************************************************************************/
/*!
	In this function, pVec0 and pVec1 are considered as 2D points.
	The squared distance between these 2 2D points is returned.
	Avoid the square root
 */
 /**************************************************************************/
template <typename T>
T Vec2SquareDistance(const Vector<T>& pVec0, const Vector<T>& pVec1) {
	Vector tem(pVec0);
	tem -= pVec1;
	return Vec2SquareLength(tem);
}

/**************************************************************************/
/*!
	This function returns the dot product between pVec0 and pVec1
 */
 /**************************************************************************/
template <typename T>
T Vec2DotProduct(const Vector<T>& pVec0, const Vector<T>& pVec1) {
	return T((pVec0.x * pVec1.x) + (pVec0.y * pVec1.y));
}

/**************************************************************************/
/*!
	This function returns the cross product magnitude
	between pVec0 and pVec1
 */
 /**************************************************************************/
template <typename T>
T Vec2CrossProductMag(const Vector<T>& pVec0, const Vector<T>& pVec1) {
	return T((pVec0.x * pVec1.y) - (pVec0.y * pVec1.x));
}




//float vec2
using Vec2 = Vector<float>;
//int vec2
using iVec2 = Vector<int>;
//unsigned int vec2
using uiVec2 = Vector<unsigned int>;
#endif
