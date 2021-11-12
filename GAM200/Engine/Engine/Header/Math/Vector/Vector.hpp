/* Start Header**********************************************************************************/
/*
@file    Vector.hpp
@author  tan wei ling felicia	weilingfelicia.tan@digipen.edu	100%
@date    16/06/2021
\brief

This file SHOULD be included to use Vector2 and Vector3 and its functions
Usage:
	#include "Vector.hpp"
	Math::vec2 testA(1, 2);
	Math::vec2 testB(2, 3);
	float a = MathD::crossProduct (testA, testB);
	Math::vec3 testA(1, 2, 4);
	Math::vec3 testB(2, 3, 5);
	Math::vec3 ans = MathD::crossProduct (testA, testB);
	MathD namespace is to prevent name clash with other library
	This file has other types of vector2d and vector3d in case it is needed
	Do add more here if other types is needed

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef VECTOR_ALL_HPP
#define VECTOR_ALL_HPP

#include "Engine/Header/Math/Vector/Vector2D.hpp"
#include "Engine/Header/Math/Vector/Vector3D.hpp"
#include "Engine/Header/Math/Vector/Vector4D.hpp"

namespace Engine {
	namespace DreamMath {
		//float vec2
		using vec2 = MathImplementation::Vector2D<float>;
		//int vec2
		using ivec2 = MathImplementation::Vector2D<int>;
		//unsigned int vec2
		using uvec2 = MathImplementation::Vector2D<unsigned int>;

		//float vec3
		using vec3 = MathImplementation::Vector3D<float>;
		//int vec3
		using ivec3 = MathImplementation::Vector3D<int>;
		//unsigned int vec3
		using uvec3 = MathImplementation::Vector3D<unsigned int>;
		
		//float vec4
		using vec4 = MathImplementation::Vector4D<float>;
		//int vec4
		using ivec4 = MathImplementation::Vector4D<int>;
		//unsigned int vec4
		using uvec4 = MathImplementation::Vector4D<unsigned int>;
	}
}

#endif
