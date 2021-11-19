/* Start Header**********************************************************************************/
/*
@file    ParticleComponent.cpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    19/11/2021
\brief
This file contains the ParticleComponent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"

#include "Engine/Header/ECS/Component/Graphics/ParticleComponent.hpp"
#include "Engine/Header/Management/ResourceManager.hpp"
#include "Engine/Header/Graphic/ResourceSet.hpp"

#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine
{
	// Contructor for Particle Component
	ParticleComponent::ParticleComponent(Entity_id _ID, const std::string _path, bool _active) :
		IComponent{ _ID }, filepath{ _path }, texobj_hdl{ 0 }, width{ 0 }, height{ 0 }, BPP{ 0 },
		minUV{ 0.f, 0.f }, maxUV{ 1.0f, 1.0f }, isActive{ _active } {}


	void ParticleComponent::ParticleUpdate(float _dt)
	{
		//for (auto& particle : m_ParticlePool)
		{
			if (!particle.Active)
				continue;

			if (particle.LifeRemaining <= 0.0f)
			{
				particle.Active = false;
				continue;
			}

			particle.LifeRemaining -= ts;
			particle.Position += particle.Velocity * (float)ts;
			particle.Rotation += 0.01f * ts;
		}
	}







	// Deserialize function for Particle Component
	ParticleComponent& ParticleComponent::Deserialize(const DSerializer& _serializer)
	{
		GraphicImplementation::SetTexture(this, std::move(_serializer.GetValue<std::string>("Filepath")));

		offsetPosition = _serializer.GetValue<Math::vec2>("OffsetPosition");
		rotation = _serializer.GetValue<float>("Rotation");
		sizeBegin = _serializer.GetValue<float>("SizeBegin");
		sizeEnd = _serializer.GetValue<float>("SizeEnd");
		velocity = _serializer.GetValue<Math::vec2>("Velocity");
		
		colorBegin = _serializer.GetValue<Math::vec2>("ColorBegin");
		colorEnd = _serializer.GetValue<Math::vec2>("ColorEnd");

		lifeTime = _serializer.GetValue<float>("LifeTime");
		lifeRemaining = _serializer.GetValue<float>("LifeRemaining");

		isActive = _serializer.GetValue<bool>("IsActive");

		return *this;
	}

	// Serialize function for Transform Component
	void ParticleComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("Filepath", filepath);

		_serializer.SetValue("OffsetPosition", offsetPosition);
		_serializer.SetValue("Rotation", rotation);
		_serializer.SetValue("SizeBegin", sizeBegin);
		_serializer.SetValue("SizeEnd", sizeEnd);
		_serializer.SetValue("Velocity", velocity);

		_serializer.SetValue("ColorBegin", colorBegin);
		_serializer.SetValue("ColorEnd", colorEnd);

		_serializer.SetValue("LifeTime", lifeTime);
		_serializer.SetValue("LifeRemaining", lifeRemaining);

		_serializer.SetValue("IsActive", isActive);
	}
}