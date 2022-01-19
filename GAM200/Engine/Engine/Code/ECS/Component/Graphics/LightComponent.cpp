/* Start Header**********************************************************************************/
/*
@file    LightComponent.cpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    19/01/2021
\brief
This file contains the LightComponent definition


Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"

#include "Engine/Header/ECS/Component/Graphics/LightComponent.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"


namespace Engine
{
	// Contructor for Light Component
	LightComponent::LightComponent(Entity_id _ID, Math::vec4 _colour, bool _active) :
		IComponent{ _ID }, colour{ _colour }, isActive{ _active } {}

	// Destructor for Light Component
	LightComponent::~LightComponent()
	{
		// Do something here
	}

	// Deserialize function for Light Component
	LightComponent& LightComponent::Deserialize(const DSerializer& _serializer)
	{
		colour = _serializer.GetValue<Math::vec4>("Colour");
		isActive = _serializer.GetValue<bool>("IsActive");

		return *this;
	}

	// Serialize function for Light Component
	void LightComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("Colour", colour);
		_serializer.SetValue("IsActive", isActive);
	}
}