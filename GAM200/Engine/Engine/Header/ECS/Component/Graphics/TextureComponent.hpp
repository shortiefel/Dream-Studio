/* Start Header**********************************************************************************/
/*
@file    TextureComponent.hpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    02/07/2021
@brief
This file contain the TextureComponent declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef TEXTURE_COMPONENT_HPP
#define TEXTURE_COMPONENT_HPP

#include "Engine/Header/pch.hpp"

#include "Engine/Header/Graphic/GraphicOptions.hpp"
#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/ECS/Component/IComponent.hpp"


namespace Engine
{
	class DSerializer;
	class SSerializer;

	struct TextureComponent : public IComponent
	{
		GraphicShape mdl_ref = GraphicShape{};
		GraphicLayer layerIndex = GraphicLayer{};

		std::string filepath = "";
		GLuint texobj_hdl = GLuint{};

		GLint width = GLint{}, height = GLint{}, BPP = GLint{}; //BPP - bits per pixel

		bool isActive = true;

		TextureComponent(const TextureComponent&) = default;
		~TextureComponent();

		TextureComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "",
			GraphicShape _shape = GraphicShape::SQUARE, bool _active = true, GraphicLayer _layer = GraphicLayer::GO);

		TextureComponent& operator= (const TextureComponent&) = default;

		TextureComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);
	};
}

#endif