/* Start Header**********************************************************************************/
/*
@file    TransformComponent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file contain the transform struct to be used by the ECS and various system


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Math/Vector.hpp"

//Scale value for circle in both axis is same
struct Transform {
	MathD::Vec2 pos = MathD::Vec2{}; //x and y for 2d position and z for the layering (whether it appear on top or below)
	MathD::Vec2 scale = MathD::Vec2{};
	float rotation = float{}; // in degree
	int layer = 0; //layer which object is placed in higher number is drawn first (they appear behind)

	Transform() = default;
	Transform(MathD::Vec2 tPos, MathD::Vec2 tScale, float tAngle, int tLayer = 0) :
		pos{ tPos }, scale{ tScale }, rotation{ tAngle }, layer{ tLayer } {}
};

#endif