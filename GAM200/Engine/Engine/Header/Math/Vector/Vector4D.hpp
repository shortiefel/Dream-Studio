/* Start Header**********************************************************************************/
/*
@file    Vector4D.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    02/10/2021
@brief

This file contain the template implementation of Vector4D
This file SHOULD NOT be included, instead use Vector.hpp
namespace MathImplementation is to prevent accidental usage

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef Vector4D_H
#define Vector4D_H

#include <iostream> // for operator<< 
#include "Engine/Header/Math/Vector/Vector2D.hpp"

namespace Engine {
	namespace DreamMath {
		namespace MathImplementation {
			template <typename T>
			class Vector4D {
			public:
				union { T x, r, s; };
				union { T y, g, t; };
				union { T z, b, u; };
				union { T w, a, v; };

				// Constructors
				Vector4D() : x{ T{} }, y{ T{} }, z{ T{} }, w{ T{} } {};
				Vector4D(T _x, T _y, T _z, T _w) : x{ _x }, y{ _y }, z{ _z }, w{ _w } {}

				/*---------------------------------------------------------------------------------------------------------------------
				* Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector4D<T>& operator = (const Vector4D<U>& rhs) {
					x = static_cast<T>(rhs.x);
					y = static_cast<T>(rhs.y);
					z = static_cast<T>(rhs.z);
					w = static_cast<T>(rhs.w);
					return *this;
				}

				template<typename U>
				Vector4D<T>& operator = (U rhs) {
					x = static_cast<T>(rhs);
					y = static_cast<T>(rhs);
					z = static_cast<T>(rhs);
					w = static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Add Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector4D<T>& operator += (const Vector4D<U>& rhs) {
					x += static_cast<T>(rhs.x);
					y += static_cast<T>(rhs.y);
					z += static_cast<T>(rhs.z);
					w += static_cast<T>(rhs.w);
					return *this;
				}

				template<typename U>
				Vector4D<T>& operator += (U rhs) {
					x += static_cast<T>(rhs);
					y += static_cast<T>(rhs);
					z += static_cast<T>(rhs);
					w += static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Minus Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector4D<T>& operator -= (const Vector4D<U>& rhs) {
					x -= static_cast<T>(rhs.x);
					y -= static_cast<T>(rhs.y);
					z -= static_cast<T>(rhs.z);
					w -= static_cast<T>(rhs.w);
					return *this;
				}

				template<typename U>
				Vector4D<T>& operator -= (U rhs) {
					x -= static_cast<T>(rhs);
					y -= static_cast<T>(rhs);
					z -= static_cast<T>(rhs);
					w -= static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Multiply Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector4D<T>& operator *= (const Vector4D<U>& rhs) {
					x *= static_cast<T>(rhs.x);
					y *= static_cast<T>(rhs.y);
					z *= static_cast<T>(rhs.z);
					w *= static_cast<T>(rhs.w);
					return *this;
				}

				template<typename U>
				Vector4D<T>& operator *= (U rhs) {
					x *= static_cast<T>(rhs);
					y *= static_cast<T>(rhs);
					z *= static_cast<T>(rhs);
					w *= static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Divide Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector4D<T>& operator /= (const Vector4D<U>& rhs) {
					x /= static_cast<T>(rhs.x);
					y /= static_cast<T>(rhs.y);
					z /= static_cast<T>(rhs.z);
					w /= static_cast<T>(rhs.w);
					return *this;
				}

				template<typename U>
				Vector4D<T>& operator /= (U rhs) {
					x /= static_cast<T>(rhs);
					y /= static_cast<T>(rhs);
					z /= static_cast<T>(rhs);
					w /= static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Pre/post increment
				---------------------------------------------------------------------------------------------------------------------*/
				Vector4D<T>& operator++() {
					++x;
					++y;
					++z;
					++w;
					return *this;
				}

				Vector4D<T>& operator--() {
					--x;
					--y;
					--z;
					--w;
					return *this;
				}

				Vector4D<T> operator++(int) {
					Vector4D<T> Result(*this);
					++* this;
					return Result;
				}

				Vector4D<T> operator--(int) {
					Vector4D<T> Result(*this);
					--* this;
					return Result;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Unary operator
				---------------------------------------------------------------------------------------------------------------------*/
				Vector4D<T> operator-() const {
					return Vector4D<T>(-x, -y, -z, -w);
				}

				Vector4D<T> operator+() const {
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* ostream operator
				---------------------------------------------------------------------------------------------------------------------*/
				friend std::ostream& operator<<(std::ostream& os, const Vector4D<T>& rhs) {
					os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << ")";
					return os;
				}

			};

			/*---------------------------------------------------------------------------------------------------------------------
			* Binary Add
			---------------------------------------------------------------------------------------------------------------------*/
			template <typename T, typename U>
			Vector4D<T> operator + (const Vector4D<T>& lhs, const Vector4D<U>& rhs) {
				return Vector4D<T>(
					lhs.x + static_cast<T>(rhs.x),
					lhs.y + static_cast<T>(rhs.y),
					lhs.z + static_cast<T>(rhs.z),
					lhs.w + static_cast<T>(rhs.w));
			}
			/*---------------------------------------------------------------------------------------------------------------------
			* Binary Minus
			---------------------------------------------------------------------------------------------------------------------*/
			template <typename T, typename U>
			Vector4D<T> operator - (const Vector4D<T>& lhs, const Vector4D<U>& rhs) {
				return lhs + -rhs;
			}
			/*---------------------------------------------------------------------------------------------------------------------
			* Binary Multiply
			---------------------------------------------------------------------------------------------------------------------*/
			template <typename T, typename U>
			Vector4D<T> operator * (const Vector4D<T>& lhs, const Vector4D<U>& rhs) {
				return Vector3D<T>(
					lhs.x * static_cast<T>(rhs.x),
					lhs.y * static_cast<T>(rhs.y),
					lhs.z * static_cast<T>(rhs.z),
					lhs.w * static_cast<T>(rhs.w));
			}

			template <typename T, typename U>
			Vector4D<T> operator * (const Vector4D<T>& lhs, U rhs) {
				return Vector3D<T>(
					lhs.x * static_cast<T>(rhs),
					lhs.y * static_cast<T>(rhs),
					lhs.z * static_cast<T>(rhs),
					lhs.w * static_cast<T>(rhs));
			}

			template <typename T, typename U>
			Vector4D<T> operator * (U lhs, const Vector4D<T>& rhs) {
				return rhs * lhs;
			}
			/*---------------------------------------------------------------------------------------------------------------------
			* Binary Divide
			---------------------------------------------------------------------------------------------------------------------*/
			template <typename T, typename U>
			Vector4D<T> operator / (const Vector4D<T>& lhs, const Vector4D<U>& rhs) {
				return Vector4D<T>(
					lhs.x / static_cast<T>(rhs.x),
					lhs.y / static_cast<T>(rhs.y),
					lhs.z / static_cast<T>(rhs.z),
					lhs.w / static_cast<T>(rhs.w));
			}

			template <typename T, typename U>
			Vector4D<T> operator / (const Vector4D<T>& lhs, U rhs) {
				return Vector4D<T>(
					lhs.x / static_cast<T>(rhs),
					lhs.y / static_cast<T>(rhs),
					lhs.z / static_cast<T>(rhs),
					lhs.w / static_cast<T>(rhs));
			}
		}
	}
}

#endif

