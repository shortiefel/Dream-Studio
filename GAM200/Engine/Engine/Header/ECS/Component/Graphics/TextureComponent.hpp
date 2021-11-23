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

	struct AnimationState
	{
		AnimationState(std::string _stateName = "", int _stateRow = 1, int _startX = 1, int _endX = 1, float _fTime = 0.1, bool _isLoop = true);

		std::string stateName;

		int stateRow, startX, endX, currFrame;

		float aTime; // Animation time
		float fTime; // Time per frame

		bool isLoop = true;		// Is texture looping? (Animation)
		bool aComplete = false; // Is animation completed?
	};

	struct TextureComponent : public IComponent
	{
		std::string filepath;
		std::string textureName;
		GLuint texobj_hdl{};

		GraphicShape mdl_ref = GraphicShape{};

		GLint width{}, height{};
		GLint BPP{}; // Bits per pixel

		bool isActive = true;

		// For animations
		bool isAnimation;

		int totalColumns, totalRows;
		float cellWidth, cellHeight;

		std::string startAnimationState;
		std::string currAnimationState;
		std::unordered_map <std::string, AnimationState> animationStateList{};

		Math::vec2 minUV, maxUV; // To be passed to shader files (batch rendering)

		// To be called by inspector
		void AddRefreshAnimationState(AnimationState _state);
		//void AddRefreshAnimationState(std::string _stateName, AnimationState _state);
		void AddRefreshAnimationState(std::string _stateName = "Default", int _stateRow = 0, int _startX = 0, int _endX = 1, float _fTime = 0.1, bool _isLoop = true);

		// Animation functions (used internally)
		void AnimationStateRename(std::string oldName, std::string newName);
		void AnimationUpdate(float _dt, AnimationState& _state);
		void SetUV(AnimationState& _state);


		TextureComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "Assets\\Textures\\Default_Square.png",
			GraphicShape _shape = GraphicShape::SQUARE, bool _animation = false, std::string _currAnimationState = "", bool _active = true);


		TextureComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		TextureComponent(const TextureComponent&) = default;
		~TextureComponent();

		TextureComponent& operator=(const TextureComponent&) = default;
	};
}

#endif