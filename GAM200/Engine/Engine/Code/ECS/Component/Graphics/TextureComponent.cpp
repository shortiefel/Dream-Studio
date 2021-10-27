/* Start Header**********************************************************************************/
/*
@file    TextureComponent.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    02/07/2021
\brief
This file contain the TextureComponent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "Engine/Header/Management/TextureManager.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine
{
	TextureComponent::TextureComponent(Entity_id _ID, const std::string _path,
		GraphicShape _shape, bool _active, GraphicLayer _layer) :
		IComponent{ _ID },
		texobj_hdl{ 0 }, filepath{ _path }, width{ 0 }, height{ 0 }, BPP{ 0 },
		mdl_ref{ _shape },
		isActive{ _active },
		layerIndex{ _layer }  {}

	TextureComponent::~TextureComponent()
	{
		//now done by TextureManager destroy function
	}

	TextureComponent& TextureComponent::Deserialize(const DSerializer& _serializer)
	{
		filepath = _serializer.GetValue<std::string>("Filepath");
		texobj_hdl = TextureManager::GetInstance().LoadTexture(filepath, &width, &height, &BPP, 4);
		mdl_ref = GraphicShape(_serializer.GetValue<int>("Shape"));
		isActive = _serializer.GetValue<bool>("IsActive");
		layerIndex = GraphicLayer(_serializer.GetValue<int>("Layer"));
		return *this;
	}

	void TextureComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("Filepath", filepath);
		_serializer.SetValue("Shape", int(mdl_ref));
		_serializer.SetValue("IsActive", isActive);
		_serializer.SetValue("Layer", int(layerIndex));

		//_serializer.EndSerialize("Texture");
	}
}