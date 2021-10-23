/* Start Header**********************************************************************************/
/*
@file    Vector3D.hpp
@author  Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
@date    16/06/2021
@brief

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
#include "Engine/Header/Math/Vector/Vector2D.hpp"

namespace Engine {
	namespace DreamMath {
		namespace MathImplementation {
			template <typename T>
			class Vector3D {
			public:
				union { T x, r, s; };
				union { T y, g, t; };
				union { T z, b, u; };

				// Constructors
				Vector3D() : x{ T{} }, y{ T{} }, z{ T{} } {};
				Vector3D(T _x, T _y, T _z) : x{ _x }, y{ _y }, z{ _z } {}
				//Vector3D(Vector2D<T> t, T z = T{}) : x{ t.x }, y{ t.y }, z{ z } {}

				/*---------------------------------------------------------------------------------------------------------------------
				* Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector3D<T>& operator = (const Vector3D<U>& rhs) {
					x = static_cast<T>(rhs.x);
					y = static_cast<T>(rhs.y);
					z = static_cast<T>(rhs.z);
					return *this;
				}

				template<typename U>
				Vector3D<T>& operator = (U rhs) {
					x = static_cast<T>(rhs);
					y = static_cast<T>(rhs);
					z = static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Add Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector3D<T>& operator += (const Vector3D<U>& rhs) {
					x += static_cast<T>(rhs.x);
					y += static_cast<T>(rhs.y);
					z += static_cast<T>(rhs.z);
					return *this;
				}

				template<typename U>
				Vector3D<T>& operator += (U rhs) {
					x += static_cast<T>(rhs);
					y += static_cast<T>(rhs);
					z += static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Minus Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector3D<T>& operator -= (const Vector3D<U>& rhs) {
					x -= static_cast<T>(rhs.x);
					y -= static_cast<T>(rhs.y);
					z -= static_cast<T>(rhs.z);
					return *this;
				}

				template<typename U>
				Vector3D<T>& operator -= (U rhs) {
					x -= static_cast<T>(rhs);
					y -= static_cast<T>(rhs);
					z -= static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Multiply Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector3D<T>& operator *= (const Vector3D<U>& rhs) {
					x *= static_cast<T>(rhs.x);
					y *= static_cast<T>(rhs.y);
					z *= static_cast<T>(rhs.z);
					return *this;
				}

				template<typename U>
				Vector3D<T>& operator *= (U rhs) {
					x *= static_cast<T>(rhs);
					y *= static_cast<T>(rhs);
					z *= static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Divide Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector3D<T>& operator /= (const Vector3D<U>& rhs) {
					x /= static_cast<T>(rhs.x);
					y /= static_cast<T>(rhs.y);
					z /= static_cast<T>(rhs.z);
					return *this;
				}

				template<typename U>
				Vector3D<T>& operator /= (U rhs) {
					x /= static_cast<T>(rhs);
					y /= static_cast<T>(rhs);
					z /= static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Pre/post increment
				---------------------------------------------------------------------------------------------------------------------*/
				Vector3D<T>& operator++() {
					++x;
					++y;
					++z;
					return *this;
				}

				Vector3D<T>& operator--() {
					--x;
					--y;
					--z;
					return *this;
				}

				Vector3D<T> operator++(int) {
					Vector3D<T> Result(*this);
					++* this;
					return Result;
				}

				Vector3D<T> operator--(int) {
					Vector3D<T> Result(*this);
					--*this;
					return Result;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Unary operator
				---------------------------------------------------------------------------------------------------------------------*/
				Vector3D<T> operator-() const {
					return Vector3D<T>(-x, -y, -z);
				}

				Vector3D<T> operator+() const {
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* ostream operator
				---------------------------------------------------------------------------------------------------------------------*/
				friend std::ostream& operator<<(std::ostream& os, const Vector3D<T>& rhs) {
					os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
					return os;
				}

			};

			/*---------------------------------------------------------------------------------------------------------------------
			* Binary Add
			---------------------------------------------------------------------------------------------------------------------*/
			template <typename T, typename U>
			Vector3D<T> operator + (const Vector3D<T>& lhs, const Vector3D<U>& rhs) {
				return Vector3D<T>(
					lhs.x + static_cast<T>(rhs.x), 
					lhs.y + static_cast<T>(rhs.y), 
					lhs.z + static_cast<T>(rhs.z));
			}
			/*---------------------------------------------------------------------------------------------------------------------
			* Binary Minus
			---------------------------------------------------------------------------------------------------------------------*/
			template <typename T, typename U>
			Vector3D<T> operator - (const Vector3D<T>& lhs, const Vector3D<U>& rhs) {
				return lhs + -rhs;
			}
			/*---------------------------------------------------------------------------------------------------------------------
			* Binary Multiply
			---------------------------------------------------------------------------------------------------------------------*/
			template <typename T, typename U>
			Vector3D<T> operator * (const Vector3D<T>& lhs, const Vector3D<U>& rhs) {
				return Vector3D<T>(
					lhs.x * static_cast<T>(rhs.x),
					lhs.y * static_cast<T>(rhs.y),
					lhs.z * static_cast<T>(rhs.z));
			}

			template <typename T, typename U>
			Vector3D<T> operator * (const Vector3D<T>& lhs, U rhs) {
				return Vector3D<T>(
					lhs.x * static_cast<T>(rhs),
					lhs.y * static_cast<T>(rhs),
					lhs.z * static_cast<T>(rhs));
			}

			template <typename T, typename U>
			Vector3D<T> operator * (U lhs, const Vector3D<T>& rhs) {
				return rhs * lhs;
			}
			/*---------------------------------------------------------------------------------------------------------------------
			* Binary Divide
			---------------------------------------------------------------------------------------------------------------------*/
			template <typename T, typename U>
			Vector3D<T> operator / (const Vector3D<T>& lhs, const Vector3D<U>& rhs) {
				return Vector3D<T>(
					lhs.x / static_cast<T>(rhs.x),
					lhs.y / static_cast<T>(rhs.y),
					lhs.z / static_cast<T>(rhs.z));
			}

			template <typename T, typename U>
			Vector3D<T> operator / (const Vector3D<T>& lhs, U rhs) {
				return Vector3D<T>(
					lhs.x / static_cast<T>(rhs),
					lhs.y / static_cast<T>(rhs),
					lhs.z / static_cast<T>(rhs));
			}
		}
	}
}

#endif
