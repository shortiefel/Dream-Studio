/* Start Header**********************************************************************************/
/*
@file    UIComponent.hpp
@author  Chia Yi Da		chiayida98@gmail.com
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

#ifndef UI_HPP
#define UI_HPP

#include "Engine/Header/Graphic/Graphic.hpp"

#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/ECS/Component/IComponent.hpp"


namespace Engine
{
	class DSerializer;
	class SSerializer;

	//Scale value for circle in both axis is same
	struct UIComponent : public IComponent {
		bool isActive = true;
		int layer = 0; //layer which object is placed in higher number is drawn first (they appear behind)

		GLuint texobj_hdl = GLuint{};
		std::string filepath = "";

		UIComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		UIComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "", bool _active = true, int _layer = 0);

		UIComponent(const UIComponent&) = default;
		UIComponent& operator=(const UIComponent&) = default;
	};
}
#endif