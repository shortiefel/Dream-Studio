/* Start Header**********************************************************************************/
/*
@file    LightComponent.cpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    19/01/2021
\brief
This file contains the LightComponent definition


Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"

#include "Engine/Header/ECS/Component/Graphics/LightComponent.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

#include "Engine/Header/Management/Settings.hpp"


namespace Engine
{
	// Contructor for Light Component
	LightComponent::LightComponent(Entity_id _ID, Math::vec4 _colour, bool _active) :
		IComponent{ _ID }, depthMapFBO{ 0 }, depthMap { 0 },
		colour{ _colour }, shadowWidth{ Engine::Settings::windowWidth }, shadowHeight{ Engine::Settings::windowHeight }, isActive{ _active } {}


	// Destructor for Light Component
	LightComponent::~LightComponent()
	{
		// Do something here
	}

	void LightComponent::FBOCreate()
	{
		glGenTextures(1, &depthMap);

		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	// Deserialize function for Light Component
	LightComponent& LightComponent::Deserialize(const DSerializer& _serializer)
	{
		colour = _serializer.GetValue<Math::vec4>("Colour");
		isActive = _serializer.GetValue<bool>("IsActive");

		return *this;
	}

	// Serialize function for Light Component
	void LightComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("Colour", colour);
		_serializer.SetValue("IsActive", isActive);
	}
}