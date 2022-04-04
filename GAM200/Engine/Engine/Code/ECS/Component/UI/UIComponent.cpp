/* Start Header**********************************************************************************/
/*
@file    UIComponent.cpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    16/09/2021
\brief
This file contains the UIComponent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"

#include "Engine/Header/ECS/Component/UI/UIComponent.hpp"
#include "Engine/Header/Graphic/ResourceSet.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {
	// Constructor for UI Component
	UIComponent::UIComponent(Entity_id _ID, const std::string _path, bool _active) :
		IComponent{ _ID }, filepath{ _path }, texobj_hdl{ 0 }, isActive{ _active } {}

	UIComponent::UIComponent(Entity_id entId, const UIComponent& rhs) :
		IComponent{ entId }, filepath{ rhs.filepath }, textureName{ rhs.textureName }, texobj_hdl{ rhs.texobj_hdl }, isActive{ rhs.isActive } {

	}

	// Destructor for UI Component
	UIComponent::~UIComponent()
	{
		// Done by ResourceManager::Destroy
	}

	//// Deserialize function for UI Component
	//UIComponent& UIComponent::Deserialize(const DSerializer& _serializer)
	//{
	//	GraphicImplementation::SetTexture(this, std::move(_serializer.GetValue<std::string>("Filepath")));
	//
	//	colour = _serializer.GetValue<Math::vec4>("Colour");
	//
	//	isActive = _serializer.GetValue<bool>("IsActive");
	//
	//	return *this;
	//}
	//
	//// Serialize function for UI Component
	//void UIComponent::Serialize(const SSerializer& _serializer)
	//{
	//	_serializer.SetValue("Filepath", filepath);
	//	_serializer.SetValue("Colour", colour);
	//	_serializer.SetValue("IsActive", isActive);
	//}
}