/* Start Header**********************************************************************************/
/*
@file    TransformComponent.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file contain the transform struct to be used by the ECS and various system

//Serialize list
-vec2 float:	Position
-vec2 float:    Scale
-string:		Shape
-string:		Shader


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Engine/Header/Graphic/Graphic.hpp"

#include <glm/glm.hpp>

namespace Engine {
	//Scale value for circle in both axis is same
	struct Transform {
		glm::vec2 position = glm::vec2{}; //x and y for 2d position and z for the layering (whether it appear on top or below)
		glm::vec2 scale = glm::vec2{};
		float angle = float{}; // in degree
		int layer = 0; //layer which object is placed in higher number is drawn first (they appear behind)

		//glm::mat3 mdl_to_ndc_xform = glm::mat3{};

		inline glm::mat3 GetTransform() const {
			return 
				//Translation
				glm::mat3{ glm::vec3(1.f, 0, 0),
							  glm::vec3(0, 1.f, 0),
							  glm::vec3(position.x, position.y, 1.f) }
				*
				glm::mat3{ glm::vec3(std::cos(glm::radians(angle)), std::sin(glm::radians(angle)), 0),
							  glm::vec3(-std::sin(glm::radians(angle)), std::cos(glm::radians(angle)), 0),
							  glm::vec3(0.f, 0.f, 1.f) }
				*
				//Scale
				glm::mat3{ glm::vec3(scale.x, 0, 0),
							 glm::vec3(0, scale.y, 0),
							 glm::vec3(0, 0, 1.f) };
		}

		Transform() = default;
		Transform(glm::vec2 tPos, glm::vec2 tScale, float rotationAngle, int tLayer = 0) :
			position{ tPos }, scale{ tScale }, angle{ rotationAngle },
			layer{ tLayer } {}
		Transform(const Transform&) = default;
		Transform& operator=(const Transform&) = default;
	};
}
#endif