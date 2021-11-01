/* Start Header**********************************************************************************/
/*
@file    GraphicSystem.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    16/06/2021
\brief
This file has the function definition for class GraphicsSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

//#include "pch.hpp"

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/System/GraphicSystem.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/ComponentArray.hpp"
#include "Engine/Header/Management/TextureManager.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"

#include "Engine/Header/Graphic/Mesh.hpp"
#include "Engine/Header/Graphic/Shader.hpp"
#include "Engine/Header/Graphic/GLSLShader.hpp"

#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/Graphic/GraphicOptions.hpp"
#include "Engine/Header/Management/TextureManager.hpp"
#include "Engine/Header/Debug Tools/Profiler.hpp"
#include "Engine/Header/Management/GameState.hpp"

#include "Engine/Header/Time/DeltaTime.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"

namespace Engine
{
	// forward declaration
	void TextureLayer(std::array<TextureComponent, MAX_ENTITIES>& arr, bool _isDebugDraw, int layer);

#define LAYER_COUNT 5

	void GraphicSystem::Render(Math::mat3 camMatrix, Graphic::FrameBuffer* _fbo) {
		PROFILER_START("Rendering");

		GLboolean isDebugDraw;

		if (!_fbo) isDebugDraw = GL_FALSE;
		else isDebugDraw = GL_TRUE;

		if (!isDebugDraw) fbo.Bind();
		else _fbo->Bind();

		// Set background to purple color
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		// Load shader program
		const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::DEFAULT].GetHandle();
		GraphicImplementation::UseShaderHandle(shd_ref_handle);

		GraphicImplementation::Renderer::ResetStats();
		GraphicImplementation::Renderer::BeginBatch(isDebugDraw);

		// Get texture for entity
		auto& textureArray = DreamECS::GetInstance().GetComponentArrayData<TextureComponent>();

		// Looping through all layers; batch rendering
		int layerCount = LAYER_COUNT;
		for (int i = 0; i < layerCount; i++)
		{
			TextureLayer(textureArray, isDebugDraw, i);
		}

		// for transparency of textures
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLSLShader::SetUniform("uCamMatrix", camMatrix, shd_ref_handle);

		GraphicImplementation::Renderer::EndBatch(isDebugDraw);
		GraphicImplementation::Renderer::Flush(isDebugDraw);

		// Unload shader program
		GraphicImplementation::UnUseShaderHandle();

		if (!isDebugDraw) fbo.Unbind();
		else _fbo->Unbind();

	}

	const Graphic::FrameBuffer& GraphicSystem::GetFrameBuffer() const
	{
		return fbo;
	}

	/*void GraphicSystem::SetPickingFunction(void(*fp)())
	{
		pickingFP = fp;
	}*/

	bool GraphicSystem::Create()
	{
		GraphicImplementation::setup_shdr();

		const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::DEFAULT].GetHandle();
		GraphicImplementation::UseShaderHandle(shd_ref_handle);

		auto loc = glGetUniformLocation(shd_ref_handle, "u_Textures");
		int samplers[32]{};
		for (int i = 0; i < 32; i++)
		{
			samplers[i] = i;
		}
		glUniform1iv(loc, 32, samplers);

		GraphicImplementation::UnUseShaderHandle();

		GraphicImplementation::Renderer::Init();

		fbo.Create(1280, 720);

		LOG_INSTANCE("Graphic System created");
		return true;
	}

	void GraphicSystem::Destroy()
	{
		GraphicImplementation::Renderer::Shutdown();
		LOG_INSTANCE("Graphic System destroyed");
	}

	// Loop through array and render objects based on layer, which is then pass to batch render.
	void TextureLayer(std::array<TextureComponent, MAX_ENTITIES>& arr, bool _isDebugDraw, int layer)
	{
		for (auto& texture : arr)
		{
			const Entity_id& entity_id = texture.GetEntityId();
			if (EntityId_Check(entity_id)) break;
			if (!texture.isActive) continue;

			TransformComponent* transform = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(entity_id);
			if (!transform || !transform->isActive) continue;

			if (transform->layer == layer)
			{
				if (texture.isAnimation && (texture.aComplete == false) && 
					GameState::GetInstance().GetPlaying())
				{
					float dt = DeltaTime::GetInstance().GetDeltaTime();
					texture.AnimationUpdate(dt);
				}

				GraphicImplementation::Renderer::DrawQuad(transform->position, transform->scale, transform->angle, texture.texobj_hdl, texture.min, texture.max);

				// to draw debug lines
				if (_isDebugDraw == GL_TRUE) {
					ColliderComponent* collider = DreamECS::GetInstance().GetComponentPTR<ColliderComponent>(entity_id);

					// when object has collider, get collider matrix
					if (collider != nullptr && collider->isActive)
					{
						if (texture.mdl_ref == GraphicShape::SQUARE)
						{
							GraphicImplementation::Renderer::DrawQuadDebug(collider->offset_position + transform->position,
								collider->offset_scale * transform->scale,
								collider->angle + transform->angle);
						}
						else if (texture.mdl_ref == GraphicShape::CIRCLE)
						{
							GraphicImplementation::Renderer::DrawCircleDebug(collider->offset_position + transform->position,
								collider->offset_scale * transform->scale,
								0);
						}
					}
				}
			}
		}
	}
}

/*
for (const auto& texture : textureArray)
{
	const Entity& entity = texture.GetEntity();
	if (Entity_Check(entity)) break;
	if (!texture.isActive) continue;

	TransformComponent* transform = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(entity);
	if (!transform || !transform->isActive) continue;

	GraphicImplementation::Renderer::DrawQuad(transform->position, transform->scale, transform->angle, texture.texobj_hdl);

	// to draw debug lines
	if (isDebugDraw == GL_TRUE) {
		ColliderComponent* collider = DreamECS::GetInstance().GetComponentPTR<ColliderComponent>(entity);

		// when object has collider, get collider matrix
		if (collider != nullptr)
		{
			if (texture.mdl_ref == GraphicShape::SQUARE)
			{
				GraphicImplementation::Renderer::DrawQuadDebug(collider->offset_position + transform->position,
					collider->offset_scale * transform->scale,
					transform->angle);
			}
			else if (texture.mdl_ref == GraphicShape::CIRCLE)
			{
				GraphicImplementation::Renderer::DrawCircleDebug(collider->offset_position + transform->position,
					collider->offset_scale * transform->scale,
					transform->angle);
			}
		}
	}
}
*/

/*
//Check texture because less Texture component on entity than Transform
const auto& textureArray = DreamECS::GetInstance().GetComponentArrayData<TextureComponent>();
for (const auto& texture : textureArray)
{
	const Entity& entity = texture.GetEntity();
	if (Entity_Check(entity)) break;
	if (!texture.isActive) continue;

	TransformComponent* transform = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(entity);
	if (!transform || !transform->isActive) continue;

	const auto& mdl_ref = GraphicImplementation::models[texture.mdl_ref];

	glBindVertexArray(mdl_ref.vaoid);
	glBindTextureUnit(6, texture.texobj_hdl);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Load shader program
	const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::DEFAULT].GetHandle();
	GraphicImplementation::UseShaderHandle(shd_ref_handle);

	GLSLShader::SetUniform("uTex2d", 6, shd_ref_handle);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLSLShader::SetUniform("uModel_to_NDC", camMatrix * transform->GetTransform(), shd_ref_handle);

	//glDrawElements(mdl_ref.primitive_type, mdl_ref.draw_cnt, GL_UNSIGNED_SHORT, NULL);
	glDrawArrays(mdl_ref.primitive_type, 0, mdl_ref.draw_cnt);

	// unbind VAO and unload shader program
	texture.Unbind();
	glBindVertexArray(0);

	// unload shader program
	GraphicImplementation::UnUseShaderHandle();

	// to draw debug lines
	if (isDebugDraw == GL_TRUE)
	{
		GraphicImplementation::DebugDrawCollider(entity, *transform, camMatrix);
	}
}
*/