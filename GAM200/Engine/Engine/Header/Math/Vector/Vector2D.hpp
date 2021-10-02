/* Start Header**********************************************************************************/
/*
@file    Vector2D.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
		 Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
@date    16/06/2021
@brief

This file contain the template implementation of Vector2D
This file SHOULD NOT be included, instead use Vector.hpp
namespace MathImplementation is to prevent accidental usage

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef Vector2D_H
#define Vector2D_H

#include <iostream> // for operator<< 
#include "Engine/Header/Math/Vector/Vector3D.hpp"

namespace Engine {
	namespace DreamMath {
		namespace MathImplementation {
			template <typename T>
			class Vector2D {
			public:
				union { T x, r, s; };
				union { T y, g, t; };

				// Constructors
				Vector2D() : x{ T{} }, y{ T{} } {};
				Vector2D(T _x, T _y) : x{ _x }, y{ _y } {}
				//Vector2D(Vector3D<T> t) : x{ t.x }, y{ t.y } {}

				/*---------------------------------------------------------------------------------------------------------------------
				* Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector2D<T>& operator = (const Vector2D<U>& rhs) {
					x = static_cast<T>(rhs.x);
					y = static_cast<T>(rhs.y);
					return *this;
				}

				template<typename U>
				Vector2D<T>& operator = (U rhs) {
					x = static_cast<T>(rhs);
					y = static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Add Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector2D<T>& operator += (const Vector2D<U>& rhs) {
					x += static_cast<T>(rhs.x);
					y += static_cast<T>(rhs.y);
					return *this;
				}

				template<typename U>
				Vector2D<T>& operator += (U rhs) {
					x += static_cast<T>(rhs);
					y += static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Minus Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector2D<T>& operator -= (const Vector2D<U>& rhs) {
					x -= static_cast<T>(rhs.x);
					y -= static_cast<T>(rhs.y);
					return *this;
				}

				template<typename U>
				Vector2D<T>& operator -= (U rhs) {
					x -= static_cast<T>(rhs);
					y -= static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Multiply Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector2D<T>& operator *= (const Vector2D<U>& rhs) {
					x *= static_cast<T>(rhs.x);
					y *= static_cast<T>(rhs.y);
					return *this;
				}

				template<typename U>
				Vector2D<T>& operator *= (U rhs) {
					x *= static_cast<T>(rhs);
					y *= static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Divide Assignment
				---------------------------------------------------------------------------------------------------------------------*/
				template<typename U>
				Vector2D<T>& operator /= (const Vector2D<U>& rhs) {
					x /= static_cast<T>(rhs.x);
					y /= static_cast<T>(rhs.y);
					return *this;
				}

				template<typename U>
				Vector2D<T>& operator /= (U rhs) {
					x /= static_cast<T>(rhs);
					y /= static_cast<T>(rhs);
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Pre/post increment
				---------------------------------------------------------------------------------------------------------------------*/
				Vector2D<T>& operator++() {
					++x;
					++y;
					return *this;
				}

				Vector2D<T>& operator--() {
					--x;
					--y;
					return *this;
				}

				Vector2D<T> operator++(int) {
					Vector2D<T> Result(*this);
					++* this;
					return Result;
				}

				Vector2D<T> operator--(int) {
					Vector2D<T> Result(*this);
					--* this;
					return Result;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* Unary operator
				---------------------------------------------------------------------------------------------------------------------*/
				Vector2D<T> operator-() const {
					return Vector2D<T>(-x, -y);
				}

				Vector2D<T> operator+() const {
					return *this;
				}
				/*---------------------------------------------------------------------------------------------------------------------
				* ostream operator
				---------------------------------------------------------------------------------------------------------------------*/
				friend std::ostream& operator<<(std::ostream& os, const Vector2D<T>& rhs) {
					os << "(" << rhs.x << ", " << rhs.y << ")";
					return os;
				}
			};

			/*---------------------------------------------------------------------------------------------------------------------
			* Binary Add
			---------------------------------------------------------------------------------------------------------------------*/
			template <typename T, typename U>
			Vector2D<T> operator + (const Vector2D<T>& lhs, const Vector2D<U>& rhs) {
				return Vector2D<T>(
					lhs.x + static_cast<T>(rhs.x),
					lhs.y + static_cast<T>(rhs.y));
			}
			/*---------------------------------------------------------------------------------------------------------------------
			* Binary Minus
			---------------------------------------------------------------------------------------------------------------------*/
			template <typename T, typename U>
			Vector2D<T> operator - (const Vector2D<T>& lhs, const Vector2D<U>& rhs) {
				return lhs + -rhs;
			}
			/*---------------------------------------------------------------------------------------------------------------------
			* Binary Multiply
			---------------------------------------------------------------------------------------------------------------------*/
			template <typename T, typename U>
			Vector2D<T> operator * (const Vector2D<T>& lhs, const Vector2D<U>& rhs) {
				return Vector2D<T>(
					lhs.x * static_cast<T>(rhs.x), 
					lhs.y * static_cast<T>(rhs.y));
			}

			template <typename T, typename U>
			Vector2D<T> operator * (const Vector2D<T>& lhs, U rhs) {
				return Vector2D<T>(
					lhs.x * static_cast<T>(rhs), 
					lhs.y * static_cast<T>(rhs));
			}

			template <typename T, typename U>
			Vector2D<T> operator * (U lhs, const Vector2D<T>& rhs) {
				return rhs * lhs;
			}
			/*---------------------------------------------------------------------------------------------------------------------
			* Binary Divide
			---------------------------------------------------------------------------------------------------------------------*/
			template <typename T, typename U>
			Vector2D<T> operator / (const Vector2D<T>& lhs, const Vector2D<U>& rhs) {
				return Vector2D<T>(
					lhs.x / static_cast<T>(rhs.x),
					lhs.y / static_cast<T>(rhs.y));
			}

			template <typename T, typename U>
			Vector2D<T> operator / (const Vector2D<T>& lhs, U rhs) {
				return Vector2D<T>(
					lhs.x / static_cast<T>(rhs),
					lhs.y / static_cast<T>(rhs));
			}
		}
	}
}

#endif
