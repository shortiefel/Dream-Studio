/* Start Header**********************************************************************************/
/*
@file    TextureComponent.cpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    02/07/2021
\brief
This file contains the TextureComponent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"

#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "Engine/Header/Management/ResourceManager.hpp"
#include "Engine/Header/Graphic/ResourceSet.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"


namespace Engine
{
	// Constructor for AnimationState
	AnimationState::AnimationState(std::string _stateName, int _stateRow, int _startX, int _endX, float _fTime, bool _isLoop) :
		stateName{ _stateName }, 
		stateRow { _stateRow }, startX{ _startX }, endX{ _endX }, currFrame{ _startX }, 
		fTime{ _fTime }, aTime{ 0.f },
		isLoop{ _isLoop }, aComplete{ false } {};

	// Contructor for Texture Component
	TextureComponent::TextureComponent(Entity_id _ID, const std::string _path,
		GraphicShape _shape, bool _animation, std::string _currAnimationState, bool _active) :
		IComponent{ _ID }, filepath{ _path }, mdl_ref{ _shape },
		texobj_hdl{ 0 }, width{ 0 }, height{ 0 }, BPP{ 0 }, totalRows{ 1 }, totalColumns{ 1 },
		minUV{ 0.f, 0.f }, maxUV{ 1.0f, 1.0f },
		isAnimation{ _animation }, startAnimationState{ std::string{} }, currAnimationState{ _currAnimationState },
		isActive{ _active }
	{
		GraphicImplementation::SetTexture(this, filepath);
		cellWidth = static_cast<float>(width) / totalColumns;
		cellHeight = static_cast<float>(height) / totalRows;
	}

	// Destructor for Texture Component
	TextureComponent::~TextureComponent()
	{
		// Done by ResourceManager::Destroy
	}

	// Function that updates the UV coordinates for spritesheets
	// and the frame variables for the component based on delta time
	void TextureComponent::AnimationUpdate(float _dt, AnimationState& _state)
	{
		_state.aTime += _dt;

		if (_state.aTime > _state.fTime)
		{
			_state.aTime -= _state.fTime;
			++_state.currFrame;

			if (_state.currFrame > _state.endX)
			{
				if (_state.isLoop == true)
				{
					_state.currFrame = _state.startX;
				}
				else
				{
					_state.currFrame = _state.endX;
					_state.aComplete = true;
				}
			}
			SetUV(_state);
		}
	}

	// Function that sets the UV texture coordinates; For spritesheets
	void TextureComponent::SetUV(AnimationState& _state)
	{
		minUV = { static_cast<float>((_state.currFrame - 1) * cellWidth) / width,
				  static_cast<float>((_state.stateRow - 1) * cellHeight) / height };

		maxUV = { static_cast<float>(_state.currFrame * cellWidth) / width,
				  static_cast<float>(_state.stateRow * cellHeight) / height };
	}

	// Function that finds the name in container and rename it to param
	// to be called by the editor for renaming states
	void TextureComponent::AnimationStateRename(std::string oldName, std::string newName)
	{
		if (oldName == newName) return;

		auto itr = animationStateList.find(oldName);

		if (itr != animationStateList.end()) 
		{
			AnimationState& newState = itr->second;
			newState.stateName = newName;

			AddRefreshAnimationState(newState);
			//AddRefreshAnimationState(newName, newState);
			animationStateList.erase(itr);
		}
	}

	// Function that adds/replace AnimationState to/in animationStateList;
	// to be called by the editor if they want more states
	void TextureComponent::AddRefreshAnimationState(AnimationState _state)
	//void TextureComponent::AddRefreshAnimationState(std::string _stateName, AnimationState _state)
	{
		if (animationStateList.find(_state.stateName) != animationStateList.end()) {
			int index = 1;
			while (animationStateList.find(_state.stateName) != animationStateList.end()) {
				index++;
			}
			_state.stateName += std::to_string(index);
		}
		animationStateList[_state.stateName] = _state;
	}

	// Function that adds/replace AnimationState to/in animationStateList;
	// to be called by the editor if they want more states
	void TextureComponent::AddRefreshAnimationState(std::string _stateName, int _stateRow, int _startX, int _endX, float _fTime, bool _isLoop)
	{
		AddRefreshAnimationState(AnimationState{ _stateName, _stateRow, _startX, _endX, _fTime, _isLoop });

	}

	// Deserialize function for Texture Component
	TextureComponent& TextureComponent::Deserialize(const DSerializer& _serializer)
	{
		GraphicImplementation::SetTexture(this, std::move(_serializer.GetValue<std::string>("Filepath")));

		mdl_ref = GraphicShape(_serializer.GetValue<int>("Shape"));

		// For animation
		isAnimation = _serializer.GetValue<bool>("IsAnimation");
		

		if (isAnimation) {
			totalRows = _serializer.GetValue<int>("TotalRow");
			totalColumns = _serializer.GetValue<int>("TotalColumns");

			cellWidth = static_cast<float>(width) / totalColumns;
			cellHeight = static_cast<float>(height) / totalRows;

			startAnimationState = _serializer.GetValue<std::string>("StartAnimationState");
			currAnimationState = _serializer.GetValue<std::string>("CurrentAnimationState");

			auto animationStates = _serializer.GetValueArray("AnimationState");

			for (auto& state : animationStates) {
				std::string stateName = state["StateName"].GetString();

				int stateRow = state["StateRow"].GetInt();

				int startX = state["StartFrame"].GetInt();
				int endX = state["EndFrame"].GetInt();

				float fTime = state["TimePerFrame"].GetFloat();

				bool isLoop = state["IsLoop"].GetBool();

				AnimationState animstate = AnimationState(stateName, stateRow, startX, endX, fTime, isLoop);

				animationStateList.emplace(stateName, animstate);
			}
		}

		isActive = _serializer.GetValue<bool>("IsActive");
		return *this;
	}

	// Serialize function for Texture Component
	void TextureComponent::Serialize(const SSerializer& _serializer)
	{

		_serializer.SetValue("Filepath", filepath);
		_serializer.SetValue("Shape", int(mdl_ref));

		_serializer.SetValue("IsAnimation", isAnimation);

		/*cellWidth = static_cast<float>(width) / totalColumns;
		cellHeight = static_cast<float>(height) / totalRows;*/

		if (isAnimation) {
			_serializer.SetValue("TotalRow", totalRows);
			_serializer.SetValue("TotalColumns", totalColumns);

			_serializer.SetValue("StartAnimationState", startAnimationState);
			_serializer.SetValue("CurrentAnimationState", currAnimationState);

			rapidjson::Value allAnimation(rapidjson::kArrayType);

			for (auto& [name, state] : animationStateList) {
				rapidjson::Value classObj(rapidjson::kObjectType);
				SSerializer cserializer(_serializer, classObj);

				cserializer.SetValue("StateName", state.stateName);
				cserializer.SetValue("StateRow", state.stateRow);
				cserializer.SetValue("StartFrame", state.startX);
				cserializer.SetValue("EndFrame", state.endX);
				cserializer.SetValue("TimePerFrame", state.fTime);
				cserializer.SetValue("IsLoop", state.isLoop);

				_serializer.SetValueJSonArray(allAnimation, classObj);
			}

			_serializer.SetValueJSonArray("AnimationState", allAnimation);
		}

		_serializer.SetValue("IsActive", isActive);
	}
}