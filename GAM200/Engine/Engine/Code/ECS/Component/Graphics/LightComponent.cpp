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
		IComponent{ _ID }, depthFBO{ 0 }, depthMap{ 0 }, shadowWidth{ 1024 }, shadowHeight{ 1024 },
		near_plane{ -1.0f }, far_plane{ 7.5f }, colour{ _colour }, isActive{ _active }
	{
		lightProjection = Math::OrthoGraphic(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = Math::LookAt(Math::vec3(-2.0f, 4.0f, -1.0f),
								 Math::vec3(0.0f, 0.0f, 0.0f),
								 Math::vec3(0.0f, 1.0f, 0.0f));

		lightSpace = lightProjection * lightView;
	}


	// Destructor for Light Component
	LightComponent::~LightComponent()
	{
		glDeleteFramebuffers(1, &depthFBO);
		glDeleteTextures(1, &depthMap);
	}

	// Function that creates both buffer and texture and attached the texture to the buffer
	void LightComponent::FBOCreate()
	{
		// Create framebuffer object
		glGenFramebuffers(1, &depthFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);


		// Generate depth texture
		glGenTextures(1, &depthMap);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight, 0, 
			GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);



		// Attached depth texture to depth buffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
		//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthMap, 0);
		glDrawBuffer(GL_NONE);
		//glReadBuffer(GL_NONE);
			

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG_ERROR("Error: Depth buffer is not complete");
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	// Function that binds the framebuffer object to the framebuffer
	void LightComponent::BindFBO()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
	}

	// Function that binds the depthMap
	void LightComponent::BindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, depthMap);
	}

	// Function that unbinds the framebuffer object that is attached to the framebuffer
	void LightComponent::Unbind()
	{
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