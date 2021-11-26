/* Start Header**********************************************************************************/
/*
@file    UISystem.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    24/10/2021
\brief
This file has the function definition for class UISystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/System/UISystem.hpp"
#include "Engine/Header/ECS/System/GraphicSystem.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/ComponentArray.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"

#include "Engine/Header/Graphic/Mesh.hpp"
#include "Engine/Header/Graphic/Shader.hpp"
#include "Engine/Header/Graphic/GLSLShader.hpp"

#include "Engine/Header/Parent/ParentManager.hpp"

#include "Engine/Header/Debug Tools/Profiler.hpp"

#include "Engine/Header/ECS/System/CameraSystem.hpp"

namespace Engine {
	static Math::vec2 prevPos;

	void UISystem::Render(Graphic::FrameBuffer* _fbo, Math::mat3 camMatrix, bool gameDraw) {
		PROFILER_START("Rendering");

		/*GLboolean gameDraw;
		if (!_fbo) gameDraw = GL_TRUE;
		else gameDraw = GL_FALSE;*/

//		if (gameDraw) {
//			//GraphicSystem::GetInstance().GetFrameBuffer().Bind();
//#ifdef _GAME_BUILD
//
//#else
//			//GraphicSystem::GetInstance().GetFrameBuffer().Bind();
//			_fbo->Bind();
//#endif
//		}
//		else _fbo->Bind();
#ifdef _GAME_BUILD
		_fbo;
#else
		_fbo->Bind();
#endif

		// Load shader program
		const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::DEFAULT].GetHandle();
		GraphicImplementation::UseShaderHandle(shd_ref_handle);

		GraphicImplementation::Renderer::BeginBatch(!gameDraw);

		Math::vec2 camPos = CameraSystem::GetInstance().GetPosition();
		const auto& uiArray = dreamECSGame->GetComponentArrayData<UIComponent>();
		for (const auto& ui : uiArray) {
			const Entity_id& entity_id = ui.GetEntityId();
			if (EntityId_Check(entity_id)) break;
			if (!ui.isActive) continue;

			TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(entity_id);
			if (!transform || !transform->isActive) continue;

			if (gameDraw) {
				transform->localPosition += camPos - prevPos;
				ParentManager::GetInstance().UpdateTruePos(entity_id);
				//GraphicImplementation::Renderer::DrawQuad(transform->position, transform->scale, transform->angle, ui.texobj_hdl);
			}
			//else {
			//	GraphicImplementation::Renderer::DrawQuad(transform->position, transform->scale, transform->angle, ui.texobj_hdl);
			//}
			GraphicImplementation::Renderer::DrawQuad(transform->position, transform->scale, transform->angle, ui.texobj_hdl);
		}
		prevPos = camPos;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLSLShader::SetUniform("uCamMatrix", camMatrix, shd_ref_handle);

		GraphicImplementation::Renderer::EndBatch(!gameDraw);
		GraphicImplementation::Renderer::Flush(!gameDraw);

		// unload shader program
		GraphicImplementation::UnUseShaderHandle();

		/*if (gameDraw) GraphicSystem::GetInstance().GetFrameBuffer().Unbind();
		else _fbo->Unbind();*/
#ifdef _GAME_BUILD

#else
		_fbo->Unbind();
#endif
	}

	void UISystem::Reset() {
		prevPos = CameraSystem::GetInstance().GetPosition();
	}

	bool UISystem::Create() {
		LOG_INSTANCE("UI System created");
		return true;
	}

	void UISystem::Destroy() {
		LOG_INSTANCE("UI System destroyed");
	}
}