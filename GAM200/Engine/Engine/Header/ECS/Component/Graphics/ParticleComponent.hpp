/* Start Header**********************************************************************************/
/*
@file    ParticleComponent.hpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    19/11/2021
@brief
This file contains the ParticleComponent declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef PARTICLE_COMPONENT_HPP
#define PARTICLE_COMPONENT_HPP

#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Math/MathLib.hpp"

namespace Engine
{
	class DSerializer;
	class SSerializer;

	struct ParticleProps
	{
		Math::vec2 offsetPosition{};
		Math::vec2 offset_scale;

		Math::vec2 velocity, velocityVariation;
		Math::vec4 colorBegin, colorEnd;
		float sizeBegin, sizeEnd, sizeVariation;
		float lifeTime = 1.0f;
	};

	struct ParticleComponent : public IComponent 
	{
		// Particle texture components, different from TextureComponent
		std::string filepath;
		std::string textureName;
		GLuint texobj_hdl{};

		GLint width{}, height{};
		GLint BPP{}; // Bits per pixel

		Math::vec2 minUV, maxUV;

		Math::vec2 offsetPosition;	// offset from Transform Component
		Math::vec2 offset_scale;

		Math::vec2 velocity;
		Math::vec4 colorBegin, colorEnd;
		float angle = 0.0f;

		float sizeBegin, sizeEnd;

		float lifeTime = 1.0f;
		float lifeRemaining = 0.0f;

		int emitSize = 1;

		bool isActive = true;

		void ParticleUpdate(float _dt);
		void ParticleEmit(const ParticleProps& particleProps);


		ParticleComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "Assets\\Textures\\Default_Square.png", bool _active = true);


		ParticleComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		ParticleComponent(const ParticleComponent&) = default;

		ParticleComponent& operator=(const ParticleComponent&) = default;
	};
}
#endif