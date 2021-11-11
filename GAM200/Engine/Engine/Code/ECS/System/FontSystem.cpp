/* Start Header**********************************************************************************/
/*
@file    FontSystem.cpp
@author  Chia Yi Da c.yida@digipen.edu
@date    24/10/2021
\brief
This file has the function definition for class FontSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"

#include "Engine/Header/ECS/System/FontSystem.hpp"
#include "Engine/Header/ECS/System/GraphicSystem.hpp"

#include "Engine/Header/ECS/Component/ComponentArray.hpp"

#include "Engine/Header/Graphic/Mesh.hpp"


namespace Engine
{
	void FontSystem::Render(Math::mat3 camMatrix, Graphic::FrameBuffer* _fbo)
	{
		PROFILER_START("Rendering");

		GLboolean fontDraw;
		if (!_fbo) fontDraw = GL_TRUE;
		else fontDraw = GL_FALSE;

		if (fontDraw) GraphicSystem::GetInstance().GetFrameBuffer().Bind();
		else _fbo->Bind();

		// Load font shader program
		const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::FONT_DRAW].GetHandle();
		GraphicImplementation::UseShaderHandle(shd_ref_handle);

		GraphicImplementation::Renderer::ResetFontStats();
		GraphicImplementation::Renderer::BeginFontBatch();

		const auto& fontArray = dreamECSGame->GetComponentArrayData<FontComponent>();

		for (const auto& text : fontArray)
		{
			if (!text.isFont) continue;

			// Option to not render glyph
			if (!text.isActive) continue;

			const Entity_id& entity_id = text.GetEntityId();
			if (EntityId_Check(entity_id)) break;

			// Get transformation component
			TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(entity_id);
			if (!transform || !transform->isActive) continue;

			// Editor
			if (fontDraw)
			{
				GraphicImplementation::Renderer::DrawString(transform->position, transform->scale, transform->angle, text.filepath, text.text, text.colour);
			}
			// Game
			else 
			{
				GraphicImplementation::Renderer::DrawString(transform->position, transform->scale / 75, transform->angle, text.filepath, text.text, text.colour);
			}


		}

		// For transparency of glyph textures
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Set uniform
		GLSLShader::SetUniform("uCamMatrix", camMatrix, shd_ref_handle);

		GraphicImplementation::Renderer::EndFontBatch();
		GraphicImplementation::Renderer::FlushFont();

		// Unload shader program
		GraphicImplementation::UnUseShaderHandle();

		if (fontDraw) GraphicSystem::GetInstance().GetFrameBuffer().Unbind();
		else _fbo->Unbind();
	}

	// Init function for FontSystem
	bool FontSystem::Create()
	{
		// Uniform for font shader
		const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::FONT_DRAW].GetHandle();
		GraphicImplementation::UseShaderHandle(shd_ref_handle);

		auto loc = glGetUniformLocation(shd_ref_handle, "u_FontTexture");
		int samplers[32]{};
		for (int i = 0; i < 32; i++)
		{
			samplers[i] = i;
		}
		glUniform1iv(loc, 32, samplers);

		GraphicImplementation::UnUseShaderHandle();

		// Initialise font mesh
		GraphicImplementation::Renderer::InitFont();

		LOG_INSTANCE("Font System created");
		return true;
	}

	// Destroy function for FontSystem
	void FontSystem::Destroy()
	{
		GraphicImplementation::Renderer::DeleteFont();

		LOG_INSTANCE("Font System destroyed");
	}
}