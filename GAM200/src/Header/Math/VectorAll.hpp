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