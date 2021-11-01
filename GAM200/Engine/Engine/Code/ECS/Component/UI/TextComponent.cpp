/* Start Header**********************************************************************************/
/*
@file    TextComponent.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    15/10/2021
\brief
This file contain the definition for TextComponent


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/Component/UI/TextComponent.hpp"
#include "Engine/Header/Management/AssetManager.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"
 
namespace Engine
{

	TextComponent::TextComponent(Entity_id _ID, const std::string _path, GraphicShape _shape,
		const std::string _string, bool _active, int _layer) :
		IComponent{ _ID },
		texobj_hdl{ 0 }, filepath{ _path }, width{ 0 }, height{ 0 }, BPP{ 0 },
		fontstring{ _string },
		isActive{ _active },
		layerIndex{ _layer }  {}

	TextComponent::~TextComponent()
	{
		//will be done by AssetManager destroy function
	}

	TextComponent& TextComponent::Deserialize(const DSerializer& _serializer)
	{
		filepath = _serializer.GetValue<std::string>("Filepath");
		texobj_hdl = AssetManager::GetInstance().LoadTexture(filepath, &width, &height, &BPP, 4);
		mdl_ref = GraphicShape(_serializer.GetValue<int>("Shape"));
		fontstring = _serializer.GetValue<std::string>("FontString");
		isActive = _serializer.GetValue<bool>("IsActive");
		layerIndex = _serializer.GetValue<int>("Layer");
		return *this;
	}

	void TextComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("Filepath", filepath);
		_serializer.SetValue("Shape", int(mdl_ref));
		_serializer.SetValue("FontString", fontstring);
		_serializer.SetValue("IsActive", isActive);
		_serializer.SetValue("Layer", layerIndex);
	}

	std::string TextComponent::ComponentName() const
	{
		return "TextComponent";
	}

	//std::string TextComponent::GetFontString()
	//{
	//	return fontstring;
	//}

	//glm::vec3 TextComponent::GetTextColour() const
	//{
	//	return glm::vec3{ _colour[0], _colour[1], _colour[2] };
	//}

}