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
		std::string filepath = "";
		std::string textureName = "";
		GLuint texobj_hdl = GLuint{};

		GraphicShape mdl_ref = GraphicShape{};

		GLint width, height, BPP; //BPP - bits per pixel

		bool isAnimation;
		bool isActive;

		// Animation
		int startFrame, endFrame, currFrame;
		float aTime, fTime; //fTime - time per frame; aTime - animation time
		bool isLoop, aComplete; // aComplete - is animation completed

		Math::vec2 min, max;

		void AnimationUpdate(float _dt);
		void SetUV();

		TextureComponent(const TextureComponent&) = default;
		~TextureComponent();

		TextureComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "",
						 GraphicShape _shape = GraphicShape::SQUARE,
						 bool _animation = false, bool _loop = false,
						 int _endFrame = 1, float _fTime = 0, bool _active = true);

		TextureComponent& operator= (const TextureComponent&) = default;

		//void SetTexture(std::string _filepath);

		TextureComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);
	};
}

#endif