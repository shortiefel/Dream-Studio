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
	TextureComponent::TextureComponent(Entity _ID, const std::string _path, GraphicShape _shape, bool _active) :
		IComponent{ _ID },
		texobj_hdl{ 0 }, filepath{ _path }, width{ 0 }, height{ 0 }, BPP{ 0 },
		mdl_ref{ _shape },
		isActive{ _active } {}

	TextureComponent::~TextureComponent()
	{
		//Problem is caused by ECS data being copied when moved from one part to another
		//Texture component gets copied and so destroyed afterwards which would cause the texture to be corrupted
		//now done by TextureManager destroy function
		//glDeleteTextures(1, &texobj_hdl);
	}

	void TextureComponent::Bind(GLuint _slot) const
	{
		glBindTextureUnit(_slot, texobj_hdl);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//glActiveTexture(GL_TEXTURE0 + slot);
		//glBindTexture(GL_TEXTURE_2D, texobj_hdl);
	}

	void TextureComponent::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	TextureComponent& TextureComponent::Deserialize(const DSerializer& _serializer) 
	{
		filepath = _serializer.GetValue<std::string>("Filepath");
		texobj_hdl = TextureManager::GetInstance().LoadTexture(filepath, &width, &height, &BPP, 4);
		mdl_ref = GraphicShape(_serializer.GetValue<int>("Shape"));
		//shd_ref = GraphicShader(serializer.GetValue<int>("Scale"));
		isActive = _serializer.GetValue<bool>("IsActive");
		return *this;
	}

	void TextureComponent::Serialize(const SSerializer& _serializer) 
	{
		_serializer.SetValue("Filepath", filepath);
		_serializer.SetValue("Shape", int(mdl_ref));
		_serializer.SetValue("IsActive", isActive);

		//_serializer.EndSerialize("Texture");
	}
}