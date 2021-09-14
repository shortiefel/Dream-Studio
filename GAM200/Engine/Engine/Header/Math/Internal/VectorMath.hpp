/* Start Header**********************************************************************************/
/*
@file    VectorMath.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
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
		template <typename T>
		T dot(const MI::Vector2D<T>& pVec0, const MI::Vector2D<T>& pVec1) {
			return T((pVec0.x * pVec1.x) + (pVec0.y * pVec1.y));
		}

		template <typename T>
		T dot(const MI::Vector3D<T>& pVec0, const MI::Vector3D<T>& pVec1) {
			return T((pVec0.x * pVec1.x) + (pVec0.y * pVec1.y) + (pVec0.z * pVec1.z));
		}
	}
}
#endif