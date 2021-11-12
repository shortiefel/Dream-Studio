/* Start Header**********************************************************************************/
/*
@file    UIComponent.hpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    16/09/2021
@brief
This file contains the UIComponent declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef UI_HPP
#define UI_HPP

#include "Engine/Header/ECS/Component/IComponent.hpp"

namespace Engine
{
	class DSerializer;
	class SSerializer;

	struct UIComponent : public IComponent {
		std::string filepath = "";
		std::string textureName = "";
		unsigned int texobj_hdl;

		bool isActive = true;


		UIComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "", bool _active = true);


		UIComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		UIComponent(const UIComponent&) = default;
		~UIComponent();

		UIComponent& operator=(const UIComponent&) = default;
	};
}
#endif