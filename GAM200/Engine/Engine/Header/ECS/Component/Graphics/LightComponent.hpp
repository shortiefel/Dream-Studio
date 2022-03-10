/* Start Header**********************************************************************************/
/*
@file    LightComponent.hpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    19/01/2021
@brief
This file contains the LightComponent declaration


Copyright (C) 2022 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef LIGHT_COMPONENT_HPP
#define LIGHT_COMPONENT_HPP

#include "Engine/Header/pch.hpp"

#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/Graphic/GraphicOptions.hpp"


namespace Engine
{
	class DSerializer;
	class SSerializer;

	struct LightComponent : public IComponent
	{
		unsigned int depthFBO, depthMap;
		unsigned int shadowWidth = 1024, shadowHeight = 1024;

		float near_plane = -1.f, far_plane = 7.5f;
		Math::mat4 lightProjection;
		Math::mat4 lightView;
		Math::mat4 lightSpace;

		Math::vec3 direction;

		Math::vec3 ambient;
		Math::vec3 diffuse;
		Math::vec3 specular;

		Math::vec3 colour;

		bool isActive = true;

		void FBOCreate();


		LightComponent(Entity_id _ID = DEFAULT_ENTITY_ID, 
			Math::vec3 _direction, Math::vec3 _ambient, Math::vec3 _diffuse, Math::vec3 _specular, Math::vec3 _colour = { 1.f, 1.f, 1.f }, 
			bool _active = true);


		void BindFBO();
		void BindTexture();
		void Unbind();

		LightComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		LightComponent(const LightComponent&) = default;
		~LightComponent();

		LightComponent& operator=(const LightComponent&) = default;
	};
}

#endif