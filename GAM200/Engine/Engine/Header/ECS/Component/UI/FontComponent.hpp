/* Start Header**********************************************************************************/
/*
@file    FontComponent.hpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    01/11/2021
\brief
This file contain the FontComponent declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef FONT_COMPONENT_HPP
#define FONT_COMPONENT_HPP


#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Math/MathLib.hpp"

namespace Engine
{
	class DSerializer;
	class SSerializer;

	struct FontComponent : public IComponent {
		std::string filepath = "";
		std::string fontName = "";
		std::string text = "";

		Math::vec3 colour{};

		bool isFont;

		bool isActive = true;

		FontComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		FontComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "Assets\\Fonts\\arial.ttf", std::string _text = "", bool _isFont = false,
			float _red = 1.0f, float _green = 1.0f, float _blue = 1.0f, bool _active = true);

		FontComponent(const FontComponent&) = default;
		FontComponent& operator=(const FontComponent&) = default;
		~FontComponent();
	};
}

#endif