/* Start Header**********************************************************************************/
/*
@file    TextComponent.hpp
@author  Goh See Yong Denise	g.seeyongdenise@digipen.edu
@date    27/10/2021
@brief
This file contain the FontComponent declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef TEXT_COMPONENT_HPP
#define TEXT_COMPONENT_HPP

#include "Engine/Header/pch.hpp"

#include "Engine/Header/Graphic/GraphicOptions.hpp"
#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/ECS/Component/IComponent.hpp"


namespace Engine
{
	class DSerializer;
	class SSerializer;

	struct TextComponent : public IComponent
	{
	public:
		GLuint texobj_hdl = GLuint{};

		std::string filepath = "";

		GraphicShape mdl_ref = GraphicShape{};

		bool isActive = true;

		GLint width = GLint{}, height = GLint{}, BPP = GLint{}; //BPP - bits per pixel

		TextComponent(const TextComponent&) = default;
		~TextComponent();

		TextComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "",
			GraphicShape _shape = GraphicShape::SQUARE, bool _active = true);

		TextComponent& operator= (const TextComponent&) = default;

		TextComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

	private:
		std::string font_string;
		std::string font_type;
		//color of font
		float color[4] = { 1.0f,1.0f,1.0f,1.0f }; 
	};
}

#endif