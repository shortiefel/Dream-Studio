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

#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	//Scale value for circle in both axis is same
	struct Transform {
		MathD::Vec2 pos = MathD::Vec2{}; //x and y for 2d position and z for the layering (whether it appear on top or below)
		MathD::Vec2 scale = MathD::Vec2{};
		//float rotation = float{}; // in degree
		int layer = 0; //layer which object is placed in higher number is drawn first (they appear behind)

		MathD::Mat3 mdl_to_ndc_xform;

		std::map<std::string, GraphicImplementation::GLModel>::iterator mdl_ref = GraphicImplementation::models.begin();
		std::map<std::string, GLSLShader>::iterator shd_ref = GraphicImplementation::shdrpgms.begin();

		Transform() = default;
		Transform(MathD::Vec2 tPos, MathD::Vec2 tScale, std::string shape = "Square", std::string shader = "Default", int tLayer = 0) :
			pos{ tPos }, scale{ tScale },
			mdl_ref{ GraphicImplementation::models.find(shape) },
			shd_ref{ GraphicImplementation::shdrpgms.find(shader) },
			layer{ tLayer } {}
		Transform(const Transform&) = default;
		Transform& operator=(const Transform&) = default;
	};
}
#endif