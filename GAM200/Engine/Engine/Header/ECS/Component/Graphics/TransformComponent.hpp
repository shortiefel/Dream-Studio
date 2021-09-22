/* Start Header**********************************************************************************/
/*
@file    TransformComponent.hpp
@author  Ow Jian Wen			jianwen123321@hotmail.com
		 Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
@date    19/06/2021
@brief
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

#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {
	//Scale value for circle in both axis is same
	struct Transform : public IComponent {
		Math::vec2 position = Math::vec2{}; //x and y for 2d position and z for the layering (whether it appear on top or below)
		Math::vec2 scale = Math::vec2{};
		float angle = float{}; // in degree
		bool isActive = true;
		int layer = 0; //layer which object is placed in higher number is drawn first (they appear behind)

		//Math::mat3 mdl_to_ndc_xform = Math::mat3{};

		Math::mat3 GetTransform() const;

		Transform Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		Transform() = default;
		Transform(Entity _ID, Math::vec2 _pos = Math::vec2{}, Math::vec2 _scale = Math::vec2{}, float _angle = float{}, bool _active = true, int _layer = 0);
		Transform(const Transform&) = default;
		Transform& operator=(const Transform&) = default;
	};
}
#endif