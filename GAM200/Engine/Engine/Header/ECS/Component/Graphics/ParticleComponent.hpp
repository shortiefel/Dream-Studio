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
#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/Graphic/GraphicOptions.hpp"
#include "Engine/Header/Math/MathLib.hpp"

namespace Engine
{
	class DSerializer;
	class SSerializer;

	struct ParticleProps
	{
		Math::vec2 offsetPosition{};
		Math::vec2 velocity{}, velocityVariation{};
		Math::vec4 colorBegin , colorEnd;
		float sizeBegin, sizeEnd, sizeVariation;
		float lifeTime = 1.0f;
	};

	struct Particle
	{
		Math::vec2 offsetPosition;	// offset from Transform Component

		float angle = 0.0f;
		float sizeBegin, sizeEnd;

		Math::vec2 velocity;
		Math::vec4 colorBegin, colorEnd;

		float lifeTime = 1.0f;
		float lifeRemaining = 0.0f;

		bool isActive = false;
	};

	struct ParticleComponent : public IComponent 
	{
		// Particle texture components, different from TextureComponent
		std::string filepath;
		std::string textureName;
		GLuint texobj_hdl{};

		GraphicShape mdl_ref = GraphicShape{};

		GLint width{}, height{};
		GLint BPP{}; // Bits per pixel

		bool isActive = true;

		Math::vec2 minUV, maxUV;
		
		ParticleProps particleData{};
		int emitSize;

		uint32_t m_PoolIndex = 999;
		//Particle m_ParticlePool[999]{};
		std::vector<Particle> m_ParticlePool;

		void ParticleUpdate(float _dt);
		void ParticleEmit(const ParticleProps& particleProps);


		ParticleComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "Assets\\Textures\\Default_Square.png", GraphicShape _shape = GraphicShape::SQUARE, int _emitSize = 1, bool _active = true);


		ParticleComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		ParticleComponent(const ParticleComponent&) = default;

		ParticleComponent& operator=(const ParticleComponent&) = default;
	};
}
#endif