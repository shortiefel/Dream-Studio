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

#include "Engine/Header/Parent/ParentManager.hpp"

#include "Engine/Header/ECS/Component/ComponentArray.hpp"

#include "Engine/Header/Graphic/Mesh.hpp"

namespace Engine
{
	//constexpr float FONT_MULTIPLIER = 50.f;

	//static Math::vec2 prevPos;

	//void FontSystem::Render(Graphic::FrameBuffer* _fbo, Math::mat3 camMatrix, bool gameDraw)
	void FontSystem::Render(Graphic::FrameBuffer* _fbo, Math::mat3 camMatrix)
	{
		PROFILER_START("Rendering");

//		GLboolean fontDraw;
//		if (!_fbo) fontDraw = GL_TRUE;
//		else fontDraw = GL_FALSE;
//
//		if (fontDraw) {
//#ifdef _GAME_BUILD
//
//#else
//			//GraphicSystem::GetInstance().GetFrameBuffer().Bind();
//#endif
//		}
//		else _fbo->Bind();
#ifdef _GAME_BUILD
		_fbo;
#else
		_fbo->Bind();
#endif

		// Load font shader program
		const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::FONT_DRAW].GetHandle();
		GraphicImplementation::UseShaderHandle(shd_ref_handle);

		GraphicImplementation::Renderer::ResetFontStats();
		GraphicImplementation::Renderer::BeginFontBatch();

		// Set uniform
		GLSLShader::SetUniform("uCamMatrix", camMatrix, shd_ref_handle);

		//Math::vec2 camPos = CameraSystem::GetInstance().GetPosition();
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

			// Game
			//if (fontDraw)
			//{
			//	GraphicImplementation::Renderer::DrawString(transform->position, transform->scale / FONT_MULTIPLIER, transform->angle, text.filepath, text.text, text.colour);
			//}
			//// Editor
			//else 
			//{
			//	//GraphicImplementation::Renderer::DrawString(transform->position, transform->scale / 75, transform->angle, text.filepath, text.text, text.colour);
			//	GraphicImplementation::Renderer::DrawString(transform->position, transform->scale / FONT_MULTIPLIER, transform->angle, text.filepath, text.text, text.colour);
			//}
			//if (gameDraw) {
			//	//Math::vec2 camPos = CameraSystem::GetInstance().GetPosition();
			//	//transform->localPosition += camPos - prevPos;
			//	//ParentManager::GetInstance().UpdateTruePos(entity_id);
			//	//GraphicImplementation::Renderer::DrawString(transform->position, transform->scale, transform->angle, text.filepath, text.text, text.colour);
			//}
			//else {
			//	GraphicImplementation::Renderer::DrawString(transform->position, transform->scale, transform->angle, text.filepath, text.text, text.colour);
			//}
			GraphicImplementation::Renderer::DrawString(transform->position, transform->scale, transform->angle, text.filepath, text.text, text.colour);
			
			//GraphicImplementation::Renderer::DrawString(transform->position, transform->scale / FONT_MULTIPLIER, transform->angle, text.filepath, text.text, text.colour);

		}
		//prevPos = camPos;

		// For transparency of glyph textures
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GraphicImplementation::Renderer::EndFontBatch();
		GraphicImplementation::Renderer::FlushFont();

		// Unload shader program
		GraphicImplementation::UnUseShaderHandle();

		/*if (fontDraw) GraphicSystem::GetInstance().GetFrameBuffer().Unbind();
		else _fbo->Unbind();*/
#ifdef _GAME_BUILD

#else
		_fbo->Unbind();
#endif
		
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