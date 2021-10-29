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

#include "Engine/Header/Debug Tools/Profiler.hpp"

#include "Engine/Header/ECS/System/CameraSystem.hpp"

namespace Engine {
	void UISystem::Render(Math::mat3 camMatrix, Graphic::FrameBuffer* _fbo) {
		PROFILER_START("Rendering");

		GLboolean gameDraw;
		if (!_fbo)
			gameDraw = GL_TRUE;
		else
			gameDraw = GL_FALSE;

		//GraphicImplementation::BindFramebuffer();
		if (gameDraw)
			GraphicSystem::GetInstance().GetFrameBuffer().Bind();
		else
			_fbo->Bind();

		// Load shader program
		const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::DEFAULT].GetHandle();
		GraphicImplementation::UseShaderHandle(shd_ref_handle);

		GraphicImplementation::Renderer::BeginBatch(!gameDraw);

		const auto& uiArray = DreamECS::GetInstance().GetComponentArrayData<UIComponent>();
		for (const auto& ui : uiArray) {
			const Entity_id& entity_id = ui.GetEntityId();
			if (EntityId_Check(entity_id)) break;
			if (!ui.isActive) continue;

			TransformComponent* transform = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(entity_id);
			if (!transform || !transform->isActive) continue;
			Math::vec2 camPos = CameraSystem::GetInstance().GetPosition();
			GraphicImplementation::Renderer::DrawQuad(transform->position + camPos, transform->scale, transform->angle, ui.texobj_hdl);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//GLSLShader::SetUniform("uCamMatrix", Math::mat3{}, shd_ref_handle);
		GLSLShader::SetUniform("uCamMatrix", camMatrix, shd_ref_handle);

		GraphicImplementation::Renderer::EndBatch(!gameDraw);
		GraphicImplementation::Renderer::Flush(!gameDraw);

		// unload shader program
		GraphicImplementation::UnUseShaderHandle();

		if (gameDraw)
			GraphicSystem::GetInstance().GetFrameBuffer().Unbind();
		else
			_fbo->Unbind();
	}

	bool UISystem::Create() {
		LOG_INSTANCE("UI System created");
		return true;
	}

	void UISystem::Destroy() {
		LOG_INSTANCE("UI System destroyed");
	}
}
