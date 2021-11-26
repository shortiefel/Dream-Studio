/* Start Header**********************************************************************************/
/*
@file    GraphicSystem.cpp
@author  Chia Yi Da		c.yida@digipen.edu
@date    16/06/2021
\brief
This file contains function definition for class GraphicsSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/System/GraphicSystem.hpp"

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

#include "Engine/Header/Management/GameState.hpp"
#include "Engine/Header/Management/Settings.hpp"
#include "Engine/Header/Time/DeltaTime.hpp"

#include "Engine/Header/ECS/Component/ComponentArray.hpp"
#include "Engine/Header/ECS/Component/ComponentList.hpp"

#include "Engine/Header/Graphic/Shader.hpp"
#include "Engine/Header/Graphic/GLSLShader.hpp"
#include "Engine/Header/Graphic/Mesh.hpp"

#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/Graphic/GraphicOptions.hpp"

static float timer1 = 0.f;

namespace Engine
{
#define LAYER_COUNT 5 // Number of layers for game objects



	// Function will fill the batch render with vertices and required attributes of game objects
	// Called by RenderGameObjects function -  to render all game objects with texture
	void RenderTextureLayer(std::array<TextureComponent, MAX_ENTITIES>& arr, int layer, float _dt)
	{
		for (auto& texture : arr)
		{
			// Option to not render individual game object
			if (!texture.isActive) continue;

			const Entity_id& entity_id = texture.GetEntityId();
			if (EntityId_Check(entity_id)) break;

			// Get transformation component
			TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(entity_id);
			if (!transform || !transform->isActive) continue;

			if (transform->layer == layer)
			{
				auto itr = texture.animationStateList.find(texture.currAnimationState);

				if (itr != texture.animationStateList.end()) 
				{
					AnimationState& state = itr->second;

					// For texture animation, update texture coords
					if (texture.isAnimation &&
						state.aComplete == false &&
						GameState::GetInstance().GetPlaying())
					{
						texture.AnimationUpdate(_dt, state);
					}
				}
				GraphicImplementation::Renderer::DrawQuad(transform->position, transform->scale, transform->angle,
					texture.texobj_hdl, texture.minUV, texture.maxUV);
			}
		}
	}

	// Function will fill the batch render with vertices and required attributes of game objects
	// Called by RenderGameObjects function -  to render all game objects with particles
	void RenderParticleLayer(std::array<ParticleComponent, MAX_ENTITIES>& arr, int layer, float _dt)
	{
		for (auto& particle : arr)
		{
			// Option to not render individual game object
			if (!particle.isActive) continue;

			const Entity_id& entity_id = particle.GetEntityId();
			if (EntityId_Check(entity_id)) break;

			// Get transformation component
			TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(entity_id);
			if (!transform || !transform->isActive) continue;

			if (transform->layer == layer)
			{
				// For particles, update life time, position and rotation
				if (GameState::GetInstance().GetPlaying())
				{
					particle.ParticleEmit(particle.particleData);
					if (particle.loopComplete) particle.isActive = true;

					for (auto& p : particle.m_ParticlePool)
					{
						particle.ParticleUpdate(p, _dt, particle.isAngleRandom);

						if (!p.isActive) continue; 

						// Fade away particles, for lerping
						float life = p.lifeRemaining / p.lifeTime;
						Math::vec4 color = Math::Lerp(p.colorEnd, p.colorBegin, life);
						Math::vec2 size = Math::Lerp(p.sizeEnd, p.sizeBegin, life);
						
						GraphicImplementation::Renderer::DrawQuad(p.offsetPosition + transform->position, size, p.angle,
							particle.texobj_hdl, color);
					}
				}
			}
		}
	}

	// Function will loop through texture array of game objects and render game objects based on layer; 
	// 0 will be rendered first, followed by 1, 2 ...
	//void RenderGameObjects(Math::mat3 _camMatrix, Math::mat4 _newcamMatrix, bool _isDebugDraw)
	void RenderGameObjects(Math::mat3 _camMatrix, bool _isDebugDraw, float _dt) {
		// Load default shader program
		const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::DEFAULT].GetHandle();
		GraphicImplementation::UseShaderHandle(shd_ref_handle);

		// Set uniform
		GLSLShader::SetUniform("uCamMatrix", _camMatrix, shd_ref_handle);
		//GLSLShader::SetUniform("newCamMatrix", _newcamMatrix, shd_ref_handle);

		// Get texture array for entities
		auto& textureArray = dreamECSGame->GetComponentArrayData<TextureComponent>();
		auto& particleArray = dreamECSGame->GetComponentArrayData<ParticleComponent>();

		// Looping through all layers for game objects; batch rendering
		int layerCount = LAYER_COUNT;
		for (int i = 0; i < layerCount; i++)
		{
			RenderTextureLayer(textureArray, i, _dt);
			RenderParticleLayer(particleArray, i, _dt);
		}

		// Enable GL_BLEND for transparency of textures
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GraphicImplementation::Renderer::EndBatch(_isDebugDraw);
		GraphicImplementation::Renderer::Flush(_isDebugDraw);

		// Unload shader program
		GraphicImplementation::UnUseShaderHandle();
	}

	// Function will loop through collision array of game objects and render out the collision lines
	void RenderCollisionLines(Math::mat3 _camMatrix, bool _isDebugDraw)
	{
		// Load collision shader program
		const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::COLLISION].GetHandle();
		GraphicImplementation::UseShaderHandle(shd_ref_handle);

		// Set uniform
		GLSLShader::SetUniform("uCamMatrix", _camMatrix, shd_ref_handle);

		/*for (int i = 0; i < 9; i++) {
			std::cout << _camMatrix.m[i] << " ";
		}
		std::cout << " camMatrix\n";*/

		// Get collision array for entities
		auto& collisionArray = dreamECSGame->GetComponentArrayData<ColliderComponent>();

		// Looping through all collider component; batch rendering
		for (auto& collider : collisionArray)
		{
			// Option to not render individual game object's collider
			if (!collider.isActive) continue;

			// Get Entity ID of component
			const Entity_id& entity_id = collider.GetEntityId();
			if (EntityId_Check(entity_id)) break;

			// Get transformation component
			TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(entity_id);
			if (!transform || !transform->isActive) continue;

			// Render lines for a quad
			if (collider.cType == ColliderType::Square)
			{
				GraphicImplementation::Renderer::DrawQuadDebug(collider.offset_position + transform->position,
					collider.offset_scale * transform->scale,
					collider.angle + transform->angle);
			}
			// Render lines for circle
			else if (collider.cType == ColliderType::Circle)
			{
				GraphicImplementation::Renderer::DrawCircleDebug(collider.offset_position + transform->position,
					collider.offset_scale * transform->scale,
					0);
			}
		}

		GraphicImplementation::Renderer::EndBatch(_isDebugDraw);
		GraphicImplementation::Renderer::Flush(_isDebugDraw);

		// Unload shader program
		GraphicImplementation::UnUseShaderHandle();
	}

	// Update function for GraphicSystem
	void GraphicSystem::Render(float _dt, Graphic::FrameBuffer* _fbo, Math::mat3 camMatrix, bool gameDraw) {
	//void GraphicSystem::Render(Math::mat3 camMatrix, Math::mat4 _newcamMatrix, Graphic::FrameBuffer* _fbo, Math::mat4 _projMatrix) {
		PROFILER_START("Rendering");
		
		/*GLboolean isDebugDraw;
		if (!_fbo) isDebugDraw = GL_FALSE;
		else isDebugDraw = GL_TRUE;

		if (!isDebugDraw) {
#ifdef _GAME_BUILD

#else
			fbo.Bind();
#endif
		}
		else _fbo->Bind();*/
#ifdef _GAME_BUILD
		_fbo;
#else
		_fbo->Bind();
#endif

		GraphicImplementation::Renderer::ResetStats();
		//GraphicImplementation::Renderer::BeginBatch(isDebugDraw);
		GraphicImplementation::Renderer::BeginBatch(!gameDraw);

		// Set background to purple color
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render game objects and collision lines
		//RenderGameObjects(camMatrix, isDebugDraw);
		RenderGameObjects(camMatrix, !gameDraw, _dt);
		//if (isDebugDraw == GL_TRUE) RenderCollisionLines(camMatrix, isDebugDraw);
		if (!gameDraw) RenderCollisionLines(camMatrix, !gameDraw);

		/*if (!isDebugDraw) fbo.Unbind();
		else _fbo->Unbind();*/
#ifdef _GAME_BUILD

#else
		_fbo->Unbind();
#endif
	}

	// Function to get frame buffer
	/*const Graphic::FrameBuffer& GraphicSystem::GetFrameBuffer() const
	{
		return fbo;
	}*/

	// Init function for GraphicSystem
	bool GraphicSystem::Create()
	{
		// Setting up shader files
		GraphicImplementation::setup_shdr();

		// Load shader program
		const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::DEFAULT].GetHandle();
		GraphicImplementation::UseShaderHandle(shd_ref_handle);

		// Uniform for game object texture shader
		auto loc = glGetUniformLocation(shd_ref_handle, "u_Textures");
		int samplers[32]{};
		for (int i = 0; i < 32; i++)
		{
			samplers[i] = i;
		}
		glUniform1iv(loc, 32, samplers);

		// Unload shader program
		GraphicImplementation::UnUseShaderHandle();

		// Initialise meshes
		GraphicImplementation::Renderer::Init();

		// Create FBO; 1280 width, 720 height
		//fbo.Create(Settings::gameWidth, Settings::gameHeight);

		LOG_INSTANCE("Graphic System created");
		return true;
	}

	// Destroy function for GraphicSystem
	void GraphicSystem::Destroy()
	{
		GraphicImplementation::Renderer::Shutdown();

		LOG_INSTANCE("Graphic System destroyed");
	}
}

// Code that might be used for the future

/*void GraphicSystem::SetPickingFunction(void(*fp)())
{
	pickingFP = fp;
}*/