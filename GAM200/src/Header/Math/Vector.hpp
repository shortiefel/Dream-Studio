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

/*
This file MUST be included to use Vector2 and Vector3 and its functions
Usage:
#include "VectorAll.hpp"
MathD::Vec2 testA(1, 2);
MathD::Vec2 testB(2, 3);
float a = MathD::crossProduct (testA, testB);
MathD::Vec3 testA(1, 2, 4);
MathD::Vec3 testB(2, 3, 5);
MathD::Vec3 ans = MathD::crossProduct (testA, testB);
MathD namespace is to prevent name clash with other library
This file has other types of vector2d and vector3d in case it is needed
Do add more here if other types is needed
*/

#ifndef VECTOR_ALL_HPP
#define VECTOR_ALL_HPP

#include "Vector2D.hpp"
#include "Vector3D.hpp"

namespace MathD {
	//float vec2
	using Vec2 = Vector2D<float>;
	//int vec2
	using iVec2 = Vector2D<int>;
	//unsigned int vec2
	using uiVec2 = Vector2D<unsigned int>;

	//float vec3
	using Vec3 = Vector3D<float>;
	//int vec3
	using iVec3 = Vector3D<int>;
	//unsigned int vec3
	using uiVec3 = Vector3D<unsigned int>;
}


#endif
