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
#include "Engine/Header/Scene/SceneManager.hpp"

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

#ifdef _GAME_BUILD
	void UISystem::Render(Graphic::FrameBuffer*, Math::mat3 camMatrix) {
#else
	void UISystem::Render(Graphic::FrameBuffer * _fbo, Math::mat3 camMatrix) {
#endif
		PROFILER_START("Rendering");

#ifdef _GAME_BUILD
		
#else
		_fbo->Bind();
#endif
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GraphicImplementation::Renderer::BeginQuadBatch();

		// Load shader program
		const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::Default].GetHandle();
		GraphicImplementation::UseShaderHandle(shd_ref_handle);

		GLSLShader::SetUniform("uCamMatrix", camMatrix, shd_ref_handle);


		const auto& uiArray = dreamECSGame->GetComponentArrayData<UIComponent>();
		for (const auto& ui : uiArray) {
			const Entity_id& entity_id = ui.GetEntityId();
			if (EntityId_Check(entity_id)) break;
			if (!ui.isActive) continue;

			TransformComponent* transform = dreamECSGame->GetComponentPTR<TransformComponent>(entity_id);
			if (!transform || !transform->isActive) continue;

			GraphicImplementation::Renderer::DrawQuad(transform->position, transform->scale, transform->angle, ui.texobj_hdl, 0.f, ui.colour);
		}

		GraphicImplementation::Renderer::EndQuadBatch();
		GraphicImplementation::Renderer::FlushQuad();

		// unload shader program
		GraphicImplementation::UnUseShaderHandle();
		

#ifdef _GAME_BUILD

#else
		_fbo->Unbind();
#endif
	}

	bool UISystem::Create() {
		LOG_INSTANCE("UI System created");
		return true;
	}

	void UISystem::Destroy() {
		LOG_INSTANCE("UI System destroyed");
	}

}