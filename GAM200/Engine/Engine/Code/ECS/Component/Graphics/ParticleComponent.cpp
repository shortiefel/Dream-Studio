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

#include "Engine/Header/Random/Random.hpp"

namespace Engine
{
	// Contructor for Particle Component
	ParticleComponent::ParticleComponent(Entity_id _ID, const std::string _path, GraphicShape _shape, int _emitSize, bool _isLooping, bool _loopComplete, bool _active) :
		IComponent{ _ID }, filepath{ _path }, mdl_ref{ _shape },
		texobj_hdl{ 0 }, width{ 0 }, height{ 0 }, BPP{ 0 }, minUV{ 0.f, 0.f }, maxUV{ 1.0f, 1.0f },
		emitSize{ _emitSize }, isLooping{ _isLooping }, loopComplete{ _loopComplete },
		isActive{ _active }
	{
		m_ParticlePool.resize(1000);
	}


	void ParticleComponent::ParticleUpdate(Particle& particle, float _dt)
	{
		if (particle.lifeRemaining <= 0.0f)
		{
			particle.isActive = false;
			return;
		}

		particle.lifeRemaining -= _dt;
		particle.offsetPosition += particle.velocity * (float)_dt;
		particle.angle += 0.01f * _dt;
	}

	/*
	* \param2	False -> No rotation
				True  -> Particle rotates randomly
	* \param3	False -> Particle uses set velocity
				True  -> set velocity += either +velocityVariation/2 or -velocityVariation/2
						 If user wants particle to go in the same direction, set velocity to be half of velocityVariation axis
	*/
	void ParticleComponent::ParticleEmit(const ParticleProps& particleProps, 
		bool isAngleRandom, bool isVelocityVariation)
	{
		// Set particle's loop to be completed once container is empty
		// Stops the rendering and update of particle once it is complete
		if (!isLooping && ((m_PoolIndex - emitSize) <= 0))
		{
			loopComplete = true;
			return;
		}

		for (int i = 0; i < emitSize; i++)
		{
			Particle& particle = m_ParticlePool[m_PoolIndex];

			particle.isActive = true;

			// Position and Angle
			particle.offsetPosition = particleProps.offsetPosition;

			if (isAngleRandom)
			{
				// 360 degrees, convert to radians (done by mesh) when pass to shader
				particle.angle = Random::Float() * 360.0f;
			}

			// Velocity
			particle.velocity = particleProps.velocity;
			if (isVelocityVariation)
			{
				particle.velocity.x += particleProps.velocityVariation.x * (Random::Float() - 0.5f);
				particle.velocity.y += particleProps.velocityVariation.y * (Random::Float() - 0.5f);
			}

			// Color
			particle.colorBegin = particleProps.colorBegin;
			particle.colorEnd = particleProps.colorEnd;

			// Life Time
			particle.lifeTime = particleProps.lifeTime;
			particle.lifeRemaining = particleProps.lifeTime;

			// Size
			particle.sizeBegin = particleProps.sizeBegin;
			particle.sizeEnd = particleProps.sizeEnd;

			// Do not have 2 randoms for x and y so as to maintain shape integrity
			particle.sizeBegin += particleProps.sizeVariation * (Random::Float() - 0.5f);

			m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
		}
	}

	// Deserialize function for Particle Component
	ParticleComponent& ParticleComponent::Deserialize(const DSerializer& _serializer)
	{
		GraphicImplementation::SetTexture(this, std::move(_serializer.GetValue<std::string>("Filepath")));

		mdl_ref = GraphicShape(_serializer.GetValue<int>("Shape"));

		emitSize = _serializer.GetValue<int>("EmitSize");
		isActive = _serializer.GetValue<bool>("IsActive");

		// Particle Data
		Math::vec2 offsetPosition = _serializer.GetValue<Math::vec2>("OffsetPosition");

		Math::vec2 velocity = _serializer.GetValue<Math::vec2>("Velocity");
		Math::vec2 velocityVariation = _serializer.GetValue<Math::vec2>("VelocityVariation");

		Math::vec4 colorBegin = _serializer.GetValue<Math::vec4>("ColorBegin");
		Math::vec4 colorEnd = _serializer.GetValue<Math::vec4>("ColorEnd");

		Math::vec2 sizeBegin = _serializer.GetValue<Math::vec2>("SizeBegin");
		Math::vec2 sizeEnd = _serializer.GetValue<Math::vec2>("SizeEnd");
		Math::vec2 sizeVariation = _serializer.GetValue<Math::vec2>("SizeVariation");

		float lifeTime = _serializer.GetValue<float>("LifeTime");

		particleData = { offsetPosition, velocity, velocityVariation, 
						 colorBegin, colorEnd, sizeBegin, sizeEnd, sizeVariation, 
						 lifeTime };

		// Particle loop
		isLooping = _serializer.GetValue<bool>("IsLooping");

		return *this;
	}

	// Serialize function for Particle Component
	void ParticleComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("Filepath", filepath);
		_serializer.SetValue("Shape", int(mdl_ref));

		_serializer.SetValue("EmitSize", emitSize);
		_serializer.SetValue("IsActive", isActive);

		// Particle Data
		_serializer.SetValue("OffsetPosition", particleData.offsetPosition);

		_serializer.SetValue("Velocity", particleData.velocity);
		_serializer.SetValue("VelocityVariation", particleData.velocityVariation);

		_serializer.SetValue("ColorBegin", particleData.colorBegin);
		_serializer.SetValue("ColorEnd", particleData.colorEnd);

		_serializer.SetValue("SizeBegin", particleData.sizeBegin);
		_serializer.SetValue("SizeEnd", particleData.sizeEnd);
		_serializer.SetValue("SizeVariation", particleData.sizeVariation);

		_serializer.SetValue("LifeTime", particleData.lifeTime);

		// Particle loop
		_serializer.SetValue("IsLooping", isLooping);
	}
}