/* Start Header**********************************************************************************/
/*
@file    Vector3D.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/06/2021
\brief

This file contain the template implementation of Vector3D
This file SHOULD NOT be included, instead use Vector.hpp
namespace MathImplementation is to prevent accidental usage

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef Vector3D_H
#define Vector3D_H

#include <iostream> // for operator<< 
#include "Math/Vector2D.hpp"

namespace MathD {
	namespace MathImplementation {
		template <typename T>
		class Vector3D
		{
		public:
			T x, y, z;

			// Constructors
			Vector3D() : x{ T{} }, y{ T{} }, z{ T{} } {};
			Vector3D(T _x, T _y, T _z) : x{ _x }, y{ _y }, z{ _z } {}
			//Vector3D(Vector2D<T> t) : x{ t.x }, y{ t.y }, z{ 0.f } {}

			// Assignment operators
			Vector3D<T>& operator += (const Vector3D<T>& rhs) {
				x += rhs.x;
				y += rhs.y;
				z += rhs.z;
				return *this;
			}

			Vector3D<T>& operator -= (const Vector3D<T>& rhs) {
				return *this += -rhs;
			}

			Vector3D<T>& operator *= (T rhs) {
				x *= rhs;
				y *= rhs;
				z *= rhs;
				return *this;
			}

			Vector3D<T>& operator /= (T rhs) {
				x /= rhs;
				y /= rhs;
				z /= rhs;
				return *this;
			}

			// Unary operators
			Vector3D<T> operator-() const {
				Vector3D<T> tem;
				tem.x = -x;
				tem.y = -y;
				tem.z = -z;
				return tem;
			}

			friend std::ostream& operator<<(std::ostream& os, const Vector3D<T>& rhs) {
				os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
				return os;
			}
		};

		// Binary operators
		template <typename T>
		Vector3D<T> operator + (const Vector3D<T>& lhs, const Vector3D<T>& rhs) {
			Vector3D<T> tem(lhs.x, lhs.y, lhs.z);
			tem += rhs;
			return tem;
		}

		template <typename T>
		Vector3D<T> operator - (const Vector3D<T>& lhs, const Vector3D<T>& rhs) {
			return lhs + -rhs;
		}

		template <typename T>
		Vector3D<T> operator * (const Vector3D<T>& lhs, T rhs) {
			Vector3D<T> tem(lhs.x, lhs.y, lhs.z);
			tem *= rhs;
			return tem;
		}

		template <typename T>
		Vector3D<T> operator * (T lhs, const Vector3D<T>& rhs) {
			return rhs * lhs;
		}

		template <typename T>
		Vector3D<T> operator / (const Vector3D<T>& lhs, T rhs) {
			Vector3D<T> tem(lhs.x, lhs.y, lhs.z);
			tem /= rhs;
			return tem;
		}


		/**************************************************************************/
		/*!
			In this function, pResult will be the unit vector of pVec0
		 */
		 /**************************************************************************/
		template <typename T>
		void Normalize(Vector3D<T>& pResult, const Vector3D<T>& pVec0) {
			pResult = pVec0 / Length(pVec0);
		}

		/**************************************************************************/
		/*!
			This function returns the length of the vector pVec0
		 */
		 /**************************************************************************/
		template <typename T>
		T Length(const Vector3D<T>& pVec0) {
			return T(sqrt((pVec0.x * pVec0.x) + (pVec0.y * pVec0.y) + (pVec0.z * pVec0.z)));
		}

		/**************************************************************************/
		/*!
			This function returns the square of pVec0's length. Avoid the square root
		 */
		 /**************************************************************************/
		template <typename T>
		T LengthSq(const Vector3D<T>& pVec0) {
			return T((pVec0.x * pVec0.x) + (pVec0.y * pVec0.y) + (pVec0.z * pVec0.z));
		}

		/**************************************************************************/
		/*!
			In this function, pVec0 and pVec1 are considered as 3D points.
			The distance between these 2 3D points is returned
		 */
		 /**************************************************************************/
		template <typename T>
		T Distance(const Vector3D<T>& pVec0, const Vector3D<T>& pVec1) {
			Vector3D<T> tem(pVec0);
			tem -= pVec1;
			return Length(tem);
		}

		/**************************************************************************/
		/*!
			In this function, pVec0 and pVec1 are considered as 3D points.
			The squared distance between these 2 3D points is returned.
			Avoid the square root
		 */
		 /**************************************************************************/
		template <typename T>
		T DistanceSq(const Vector3D<T>& pVec0, const Vector3D<T>& pVec1) {
			Vector3D<T> tem(pVec0);
			tem -= pVec1;
			return LengthSq(tem);
		}

		/**************************************************************************/
		/*!
			This function returns the dot product between pVec0 and pVec1
		 */
		 /**************************************************************************/
		template <typename T>
		T DotProduct(const Vector3D<T>& pVec0, const Vector3D<T>& pVec1) {
			return T((pVec0.x * pVec1.x) + (pVec0.y * pVec1.y) + (pVec0.z * pVec1.z));
		}

		/**************************************************************************/
		/*!
			This function returns the cross product magnitude
			between pVec0 and pVec1
			returns a vector3d
		 */
		 /**************************************************************************/
		template <typename T>
		Vector3D<T> CrossProduct(const Vector3D<T>& pVec0, const Vector3D<T>& pVec1) {
			Vector3D<T> tem;
			tem.x = (pVec0.y * pVec1.z) - (pVec0.z * pVec1.y);
			tem.y = (pVec0.z * pVec1.x) - (pVec0.x * pVec1.z);
			tem.z = (pVec0.x * pVec1.y) - (pVec0.y * pVec1.x);
			return tem;
		}
	}
}

#endif

