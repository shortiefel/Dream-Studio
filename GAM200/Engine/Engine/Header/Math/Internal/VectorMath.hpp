/* Start Header**********************************************************************************/
/*
@file    VectorMath.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    14/09/2021
\brief

Math to be used with Vector as parameter

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

#include "Engine/Header/Math/Vector3D.hpp"
#include "Engine/Header/Math/Vector2D.hpp"

namespace Engine {
	namespace DreamMath {
		namespace MI = MathImplementation;

		/*-------------------------------------------------------------------------------------------------------------------
		Length
		-------------------------------------------------------------------------------------------------------------------*/
		template <typename T>
		T length(const MI::Vector2D<T>& pVec0) {
			return T(sqrt((pVec0.x * pVec0.x) + (pVec0.y * pVec0.y)));
		}

		template <typename T>
		T length(const MI::Vector3D<T>& pVec0) {
			return T(sqrt((pVec0.x * pVec0.x) + (pVec0.y * pVec0.y) + (pVec0.z * pVec0.z)));
		}

		template <typename T>
		T lengthSq(const MI::Vector2D<T>& pVec0) {
			return T((pVec0.x * pVec0.x) + (pVec0.y * pVec0.y));
		}

		template <typename T>
		T lengthSq(const MI::Vector3D<T>& pVec0) {
			return T((pVec0.x * pVec0.x) + (pVec0.y * pVec0.y) + (pVec0.z * pVec0.z));
		}

		/*-------------------------------------------------------------------------------------------------------------------
		Distance
		-------------------------------------------------------------------------------------------------------------------*/
		template <typename T>
		T distance(const MI::Vector2D<T>& pVec0, const MI::Vector2D<T>& pVec1) {
			return length(pVec0 - pVec1);
		}

		template <typename T>
		T distance(const MI::Vector3D<T>& pVec0, const MI::Vector3D<T>& pVec1) {
			return length(pVec0 - pVec1);
		}

		template <typename T>
		T distanceSq(const MI::Vector2D<T>& pVec0, const MI::Vector2D<T>& pVec1) {
			return lengthSq(pVec0 - pVec1);
		}

		template <typename T>
		T distanceSq(const MI::Vector3D<T>& pVec0, const MI::Vector3D<T>& pVec1) {
			return lengthSq(pVec0 - pVec1);
		}
		/*-------------------------------------------------------------------------------------------------------------------
		Normalize
		-------------------------------------------------------------------------------------------------------------------*/
		template <typename T>
		MI::Vector2D<T> normalize(MI::Vector2D<T>& pResult) {
			return (pResult / length(pResult));
		}

		template <typename T>
		MI::Vector3D<T> normalize(MI::Vector3D<T>& pResult) {
			return (pResult / length(pResult));
		}
		/*-------------------------------------------------------------------------------------------------------------------
		Dot product
		-------------------------------------------------------------------------------------------------------------------*/
		//The type of the first parameter is used
		template <typename T, typename U>
		T dot(const MI::Vector2D<T>& pVec0, const MI::Vector2D<U>& pVec1) {
			return T(
				(pVec0.x * static_cast<T>(pVec1.x)) +
				(pVec0.y * static_cast<T>(pVec1.y)));
		}
		//The type of the first parameter is used
		template <typename T, typename U>
		T dot(const MI::Vector3D<T>& pVec0, const MI::Vector3D<U>& pVec1) {
			return T(
				(pVec0.x * static_cast<T>(pVec1.x)) +
				(pVec0.y * static_cast<T>(pVec1.y)) +
				(pVec0.z * static_cast<T>(pVec1.z)));
		}
		//The type of the first parameter is used
		template <typename T, typename U>
		T cross(const MI::Vector2D<T>& pVec0, const MI::Vector2D<U>& pVec1) {
			return T(
				(pVec0.x * static_cast<T>(pVec1.y)) -
				(pVec0.y * static_cast<T>(pVec1.x)));
		}
		//The type of the first parameter is used
		template <typename T, typename U>
		MI::Vector3D<T> cross(const MI::Vector3D<T>& pVec0, const MI::Vector3D<U>& pVec1) {
			return MI::Vector3D<T>(
				(pVec0.y * static_cast<T>(pVec1.z)) - (pVec0.z * static_cast<T>(pVec1.y)),
				(pVec0.z * static_cast<T>(pVec1.x)) - (pVec0.x * static_cast<T>(pVec1.z)),
				(pVec0.x * static_cast<T>(pVec1.y)) - (pVec0.y * static_cast<T>(pVec1.x)));
		}		
	}			
}
#endif