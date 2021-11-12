/* Start Header**********************************************************************************/
/*
@file    TextureComponent.hpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    02/07/2021
@brief
This file contains the TextureComponent declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef TEXTURE_COMPONENT_HPP
#define TEXTURE_COMPONENT_HPP

#include "Engine/Header/pch.hpp"

#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/Graphic/GraphicOptions.hpp"


namespace Engine
{
	class DSerializer;
	class SSerializer;

	struct TextureComponent : public IComponent
	{
		std::string filepath = "";
		std::string textureName = "";
		GLuint texobj_hdl{};

		GraphicShape mdl_ref = GraphicShape{};

		GLint width{}, height{};
		GLint BPP{}; // Bits per pixel

		bool isAnimation;
		bool isActive = true;

		// Animation variables
		int startFrame, endFrame, currFrame;

		float aTime; // Animation time
		float fTime; // Time per frame

		bool isLoop;	// Is texture looping? (Animation)
		bool aComplete; // Is animation completed?

		Math::vec2 minUV, maxUV;

		void AnimationUpdate(float _dt);
		void SetUV();


		TextureComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "Assets\\Textures\\Default_Square.png",
			GraphicShape _shape = GraphicShape::SQUARE,
			bool _animation = false, bool _loop = false,
			int _endFrame = 1, float _fTime = 0, bool _active = true);


		TextureComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		TextureComponent(const TextureComponent&) = default;
		~TextureComponent();

		TextureComponent& operator=(const TextureComponent&) = default;
	};
}

#endif