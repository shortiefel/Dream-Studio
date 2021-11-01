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
#include "Engine/Header/Graphic/TextureSet.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"


namespace Engine
{
	TextureComponent::TextureComponent(Entity_id _ID, const std::string _path,
									   GraphicShape _shape,
									   bool _animation, bool _loop,
									   int _endFrame, float _fTime, bool _active) :
					IComponent{ _ID }, filepath{ _path },
					mdl_ref{ _shape },
					isAnimation{ _animation }, isLoop{ _loop }, aComplete { false},
					startFrame{ 1 }, endFrame{ _endFrame }, currFrame{ 0 },
					aTime{ 0.f }, fTime{ _fTime }, isActive{ _active },
					min{ 0.f, 0.f }, max{1.0f, 1.0f},
					texobj_hdl{ 0 }, width{ 0 }, height{ 0 }, BPP{ 0 } {}

	TextureComponent::~TextureComponent()
	{
		//now done by TextureManager destroy function
	}

	// Update frames of spritesheets
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

	void TextureComponent::SetUV()
	{
		float cellWidth = static_cast<float>(width) / endFrame;
		
		//std::cout << "WIDTH: " << width << std::endl;
		min = { static_cast<float>((currFrame - 1) * cellWidth) / width,
				0.f };

		max = { static_cast<float>(currFrame * cellWidth) / width,
				static_cast<float>(height) / height };
	}

	TextureComponent& TextureComponent::Deserialize(const DSerializer& _serializer)
	{
		GraphicImplementation::SetTexture(this, std::move(_serializer.GetValue<std::string>("Filepath")));
		/*filepath = _serializer.GetValue<std::string>("Filepath");
		texobj_hdl = TextureManager::GetInstance().LoadTexture(filepath, &width, &height, &BPP, 4);*/

		mdl_ref = GraphicShape(_serializer.GetValue<int>("Shape"));

		// For animation
		isAnimation = _serializer.GetValue<bool>("IsAnimation");
		isLoop = _serializer.GetValue<bool>("IsLoop");
		endFrame = _serializer.GetValue<int>("EndFrame");
		fTime = _serializer.GetValue<float>("TimePerFrame");

		isActive = _serializer.GetValue<bool>("IsActive");

		return *this;
	}

	void TextureComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("Filepath", filepath);
		_serializer.SetValue("Shape", int(mdl_ref));

		_serializer.SetValue("IsAnimation", isAnimation);
		_serializer.SetValue("IsLoop", isLoop);
		_serializer.SetValue("EndFrame", endFrame);
		_serializer.SetValue("TimePerFrame", fTime);

		_serializer.SetValue("IsActive", isActive);

		//_serializer.EndSerialize("Texture");
	}
}