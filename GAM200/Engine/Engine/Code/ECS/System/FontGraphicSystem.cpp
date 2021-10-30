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
#include "Engine/Header/ECS/System/FontGraphicSystem.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/ComponentArray.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "engine/Header/ECS/Component/UI/TextComponent.hpp"
#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"

#include "Engine/Header/Graphic/Mesh.hpp"
#include "Engine/Header/Graphic/Shader.hpp"
#include "Engine/Header/Graphic/GLSLShader.hpp"

//#include "Engine/Header/Graphic/Graphic.hpp"
//#include "Engine/Header/Graphic/GraphicOptions.hpp"
//#include "Engine/Header/Management/TextureManager.hpp"

#include "Engine/Header/ECS/System/CameraSystem.hpp"

#define CONSTANT_SIZE 0.2

namespace Engine {

	void FontGraphicSystem::Render(Math::mat3 camMatrix, Graphic::FrameBuffer* _fbo) {
		GLboolean fontDraw;
		if (!_fbo)
			fontDraw = GL_TRUE;
		else
			fontDraw = GL_FALSE;

		//GraphicImplementation::BindFramebuffer();
		if (fontDraw)
			GraphicSystem::GetInstance().GetFrameBuffer().Bind();
		else
			_fbo->Bind();

		// Load shader program
		const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::FONT_DRAW].GetHandle();
		GraphicImplementation::UseShaderHandle(shd_ref_handle);

		GraphicImplementation::Renderer::ResetStats();
		GraphicImplementation::Renderer::BeginBatch(!fontDraw);

		const auto& textArray = DreamECS::GetInstance().GetComponentArrayData<TextComponent>();
		for (const auto& text : textArray) {
			const Entity_id& entity_id = text.GetEntityId();
			if (EntityId_Check(entity_id)) break;
			if (!text.isActive) continue;

			TransformComponent* transform = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(entity_id);
			if (!transform || !transform->isActive) continue;

			GraphicImplementation::Renderer::DrawQuad(transform->position, transform->scale, transform->angle, text.texobj_hdl);
			font_renderer.Draw();
			// to draw debug lines
			if (fontDraw == GL_TRUE) {
				ColliderComponent* collider = DreamECS::GetInstance().GetComponentPTR<ColliderComponent>(entity_id);

				// when object has collider, get collider matrix
				if (collider != nullptr)
				{
					if (text.mdl_ref == GraphicShape::SQUARE)
					{
						GraphicImplementation::Renderer::DrawQuadDebug(collider->offset_position + transform->position,
							collider->offset_scale * transform->scale,
							transform->angle);
					}
					else if (text.mdl_ref == GraphicShape::CIRCLE)
					{
						GraphicImplementation::Renderer::DrawCircleDebug(collider->offset_position + transform->position,
							collider->offset_scale * transform->scale,
							transform->angle);
					}
				}
			}
		}


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//GLSLShader::SetUniform("uCamMatrix", Math::mat3{}, shd_ref_handle);
		GLSLShader::SetUniform("uCamMatrix", camMatrix, shd_ref_handle);

		GraphicImplementation::Renderer::EndBatch(!fontDraw);
		GraphicImplementation::Renderer::Flush(!fontDraw);

		// unload shader program
		GraphicImplementation::UnUseShaderHandle();

		if (fontDraw)
			GraphicSystem::GetInstance().GetFrameBuffer().Unbind();
		else
			_fbo->Unbind();
	}
	//Math::mat4& FontGraphicSystem::GetProjection()
	//{
	//	return proj;
	//}
	bool FontGraphicSystem::Create() {
		LOG_INSTANCE("Font System created");
		return true;
	}

	void FontGraphicSystem::Destroy() {
		LOG_INSTANCE("Font System destroyed");
	}

	
}
