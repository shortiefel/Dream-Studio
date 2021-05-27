/* Start Header**********************************************************************************/
/*!
\file Vector2D.hpp
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

This file contain the template implementation of Vector2D

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef Vector2D_H
#define Vector2D_H

template <typename T>
class Vector2D
{
public:
	T x, y;

	// Constructors
	Vector2D() : x{ T{} }, y{ T{} } {};
	Vector2D(T _x, T _y) : x{ _x }, y{ _y } {}

	// Assignment operators
	Vector2D<T>& operator += (const Vector2D<T>& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2D<T>& operator -= (const Vector2D<T>& rhs) {
		return *this += -rhs;
	}

	Vector2D<T>& operator *= (T rhs) {
		x *= rhs;
		y *= rhs;
		return *this;
	}

	Vector2D<T>& operator /= (T rhs) {
		x /= rhs;
		y /= rhs;
		return *this;
	}

	// Unary operators
	Vector2D<T> operator-() const {
		Vector2D tem;
		tem.x = -x;
		tem.y = -y;
		return tem;
	}
};

namespace MathD {
	// Binary operators
	template <typename T>
	Vector2D<T> operator + (const Vector2D<T>& lhs, const Vector2D<T>& rhs) {
		Vector2D<T> tem(lhs.x, lhs.y);
		tem += rhs;
		return tem;
	}

	template <typename T>
	Vector2D<T> operator - (const Vector2D<T>& lhs, const Vector2D<T>& rhs) {
		return lhs + -rhs;
	}

	template <typename T>
	Vector2D<T> operator * (const Vector2D<T>& lhs, T rhs) {
		Vector2D<T> tem(lhs.x, lhs.y);
		tem *= rhs;
		return tem;
	}

	template <typename T>
	Vector2D<T> operator * (T lhs, const Vector2D<T>& rhs) {
		return rhs * lhs;
	}

	template <typename T>
	Vector2D<T> operator / (const Vector2D<T>& lhs, T rhs) {
		Vector2D<T> tem(lhs.x, lhs.y);
		tem /= rhs;
		return tem;
	}


	/**************************************************************************/
	/*!
		In this function, pResult will be the unit vector of pVec0
	 */
	 /**************************************************************************/
	template <typename T>
	void normalize(Vector2D<T>& pResult, const Vector2D<T>& pVec0) {
		pResult = pVec0 / length(pVec0);
	}

	/**************************************************************************/
	/*!
		This function returns the length of the vector pVec0
	 */
	 /**************************************************************************/
	template <typename T>
	T length(const Vector2D<T>& pVec0) {
		return T(sqrt((pVec0.x * pVec0.x) + (pVec0.y * pVec0.y)));
	}

	/**************************************************************************/
	/*!
		This function returns the square of pVec0's length. Avoid the square root
	 */
	 /**************************************************************************/
	template <typename T>
	T lengthSq(const Vector2D<T>& pVec0) {
		return T((pVec0.x * pVec0.x) + (pVec0.y * pVec0.y));
	}

	/**************************************************************************/
	/*!
		In this function, pVec0 and pVec1 are considered as 2D points.
		The distance between these 2 2D points is returned
	 */
	 /**************************************************************************/
	template <typename T>
	T distance(const Vector2D<T>& pVec0, const Vector2D<T>& pVec1) {
		Vector2D<T> tem(pVec0);
		tem -= pVec1;
		return length(tem);
	}

	/**************************************************************************/
	/*!
		In this function, pVec0 and pVec1 are considered as 2D points.
		The squared distance between these 2 2D points is returned.
		Avoid the square root
	 */
	 /**************************************************************************/
	template <typename T>
	T distanceSq(const Vector2D<T>& pVec0, const Vector2D<T>& pVec1) {
		Vector2D<T> tem(pVec0);
		tem -= pVec1;
		return lengthSq(tem);
	}

	/**************************************************************************/
	/*!
		This function returns the dot product between pVec0 and pVec1
	 */
	 /**************************************************************************/
	template <typename T>
	T dotProduct(const Vector2D<T>& pVec0, const Vector2D<T>& pVec1) {
		return T((pVec0.x * pVec1.x) + (pVec0.y * pVec1.y));
	}

	/**************************************************************************/
	/*!
		This function returns the cross product magnitude
		between pVec0 and pVec1
	 */
	 /**************************************************************************/
	template <typename T>
	T crossProduct(const Vector2D<T>& pVec0, const Vector2D<T>& pVec1) {
		return T((pVec0.x * pVec1.y) - (pVec0.y * pVec1.x));
	}

}

#endif
