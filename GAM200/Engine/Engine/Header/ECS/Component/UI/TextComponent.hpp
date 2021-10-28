/* Start Header**********************************************************************************/
/*
@file    TextComponent.hpp
@author  Goh See Yong Denise	g.seeyongdenise@digipen.edu
@date    27/10/2021
@brief
This file contain the TextComponent declaration


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

		GraphicShape mdl_ref = GraphicShape{};

		GraphicLayer layerIndex = GraphicLayer{};

		std::string filepath = "";

		std::string fontstring = "";

		bool isActive = true;

		GLint width = GLint{}, height = GLint{}, BPP = GLint{}; //BPP - bits per pixel

		//void SetTextColour(const glm::vec3& colour)
		//{
		//	_colour[0] = colour.r;
		//	_colour[1] = colour.g;
		//	_colour[2] = colour.b;
		//}
		//glm::vec3 GetTextColour() const
		//{
		//	return glm::vec3{ _colour[0], _colour[1], _colour[2] };
		//}

		const std::string& GetFontType()
		{
			return font_type;
		}
		TextComponent(const TextComponent&) = default;
		~TextComponent();

		TextComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "",
			GraphicShape _shape = GraphicShape::SQUARE, const std::string _string = "", bool _active = true, GraphicLayer _layer = GraphicLayer::GO);

		TextComponent& operator= (const TextComponent&) = default;

		TextComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		std::string ComponentName() const;

		std::string& GetFontString();

	private:
		std::string font_type;
		//colour of font
		float _colour[4] = { 1.0f,1.0f,1.0f,1.0f };
	};
}

#endif