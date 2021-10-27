/* Start Header**********************************************************************************/
/*
@file    TextComponent.cpp
@author  Goh See Yong Denise	g.seeyongdenise@digipen.edu
@date    27/10/2021
\brief
This file contain the TextComponent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/Component/Graphics/TextComponent.hpp"
#include "Engine/Header/Management/AssetManager.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine
{
	TextComponent::TextComponent(Entity_id _ID, const std::string _path, GraphicShape _shape, bool _active) :
		IComponent{ _ID },
		texobj_hdl{ 0 }, filepath{ _path }, width{ 0 }, height{ 0 }, BPP{ 0 },
		mdl_ref{ _shape },
		isActive{ _active } {}

	TextComponent::~TextComponent()
	{
		//will be done by AssetManager destroy function
	}

	TextComponent& TextComponent::Deserialize(const DSerializer& _serializer)
	{
		filepath = _serializer.GetValue<std::string>("Filepath");
		texobj_hdl = AssetManager::GetInstance().LoadFont(filepath, &width, &height, &BPP, 4);
		mdl_ref = GraphicShape(_serializer.GetValue<int>("Shape"));
		isActive = _serializer.GetValue<bool>("IsActive");
		return *this;
	}

	void TextComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("Filepath", filepath);
		_serializer.SetValue("Shape", int(mdl_ref));
		_serializer.SetValue("IsActive", isActive);

		//_serializer.EndSerialize("Texture");
	}
}