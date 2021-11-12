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
	// Contructor for Texture Component
	TextureComponent::TextureComponent(Entity_id _ID, const std::string _path,
		GraphicShape _shape,
		bool _animation, bool _loop,
		int _endFrame, float _fTime, bool _active) :
		IComponent{ _ID }, filepath{ _path },
		mdl_ref{ _shape },
		isAnimation{ _animation }, isLoop{ _loop }, aComplete{ false },
		startFrame{ 1 }, endFrame{ _endFrame }, currFrame{ 0 },
		aTime{ 0.f }, fTime{ _fTime }, isActive{ _active },
		minUV{ 0.f, 0.f }, maxUV{ 1.0f, 1.0f },
		texobj_hdl{ 0 }, width{ 0 }, height{ 0 }, BPP{ 0 } {
		GraphicImplementation::SetTexture(this, filepath);
	}

	// Destructor for Texture Component
	TextureComponent::~TextureComponent()
	{
		// Done by ResourceManager::Destroy
	}

	// Function that updates the UV coordinates for spritesheets
	// and the frame variables for the component based on delta time
	void TextureComponent::AnimationUpdate(float _dt)
	{
		aTime += _dt;

		if (aTime > fTime)
		{
			aTime -= fTime;
			++currFrame;

			if (currFrame > endFrame)
			{
				if (isLoop == true)
				{
					currFrame = startFrame;
				}
				else
				{
					currFrame = endFrame;
					aComplete = true;
				}
			}

			SetUV();
		}
	}

	// Function that sets the UV texture coordinates; For spritesheets
	void TextureComponent::SetUV()
	{
		float cellWidth = static_cast<float>(width) / endFrame;

		minUV = { static_cast<float>((currFrame - 1) * cellWidth) / width,
				0.f };

		maxUV = { static_cast<float>(currFrame * cellWidth) / width,
				static_cast<float>(height) / height };
	}

	// Deserialize function for Texture Component
	TextureComponent& TextureComponent::Deserialize(const DSerializer& _serializer)
	{
		GraphicImplementation::SetTexture(this, std::move(_serializer.GetValue<std::string>("Filepath")));

		mdl_ref = GraphicShape(_serializer.GetValue<int>("Shape"));

		// For animation
		isAnimation = _serializer.GetValue<bool>("IsAnimation");
		isLoop = _serializer.GetValue<bool>("IsLoop");
		endFrame = _serializer.GetValue<int>("EndFrame");
		fTime = _serializer.GetValue<float>("TimePerFrame");

		isActive = _serializer.GetValue<bool>("IsActive");

		return *this;
	}

	// Serialize function for Texture Component
	void TextureComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("Filepath", filepath);
		_serializer.SetValue("Shape", int(mdl_ref));

		_serializer.SetValue("IsAnimation", isAnimation);
		_serializer.SetValue("IsLoop", isLoop);
		_serializer.SetValue("EndFrame", endFrame);
		_serializer.SetValue("TimePerFrame", fTime);

		_serializer.SetValue("IsActive", isActive);
	}
}