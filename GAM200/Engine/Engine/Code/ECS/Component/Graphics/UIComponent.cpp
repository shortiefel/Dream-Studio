/* Start Header**********************************************************************************/
/*
@file    UIComponent.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    16/09/2021
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

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/Component/Graphics/UIComponent.hpp"

#include "Engine/Header/Management/TextureManager.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {
	UIComponent::UIComponent(Entity _ID, const std::string _path, bool _active, int _layer) :
		IComponent{ _ID },
		filepath{ _path }, isActive{ _active }, layer{ _layer }, texobj_hdl{ 0 } {}

	UIComponent& UIComponent::Deserialize(const DSerializer& _serializer) {
		filepath = _serializer.GetValue<std::string>("Filepath");
		isActive = _serializer.GetValue<bool>("IsActive");

		GLint width = GLint{}, height = GLint{}, BPP = GLint{};
		texobj_hdl = TextureManager::GetInstance().LoadTexture(filepath, &width, &height, &BPP, 4);
		return *this;
	}

	void UIComponent::Serialize(const SSerializer& _serializer) {
		_serializer.SetValue("Filepath", filepath);
		_serializer.SetValue("IsActive", isActive);
	}
}