/* Start Header**********************************************************************************/
/*
@file    DebugDraw.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    23/09/2021
\brief
This file contains the definition of functions that allows users to
draw debug lines for game objects


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/DreamECS.hpp"

#include "Engine/Header/Graphic/DebugDraw.hpp"
#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/Graphic/GraphicOptions.hpp"

#define rad(ang) \
	Math::radians((float)ang)

#define vec3(a, b, c) \
	Math::vec3(a, b, c)

namespace Engine 
{
	namespace GraphicImplementation 
	{
		void DebugDrawCollider(Entity const& entity, TransformComponent const& transform, Math::mat3 camMatrix) 
		{
			ColliderComponent* collider = DreamECS::GetInstance().GetComponentPTR<ColliderComponent>(entity);

			// when object has collider, get collider matrix
			if (collider != nullptr) 
			{
				GraphicShape debugShape = (collider->cType == ColliderType::CIRCLE) ? 
										GraphicShape::DEBUG_CIRCLE : GraphicShape::DEBUG_BOX;

				// Bind VAO
				const auto colliderDebug = models[debugShape];
				glBindVertexArray(colliderDebug.vaoid);

				// Load DEBUG_DRAW shader program
				const auto& shd_ref_handle = shdrpgms[GraphicShader::DEBUG_DRAW].GetHandle();
				UseShaderHandle(shd_ref_handle);

				// p = position, s = scale
				Math::vec2 p = collider->offset_position + transform.position;
				Math::vec2 s = collider->offset_scale * transform.scale;

				// Compute collider matrix
				Math::mat3 colliderMat = {
					// Translate
					Math::mat3{ vec3(1.f, 0, 0),
								vec3(0, 1.f, 0),
								vec3(p.x, p.y, 1.f) }
					*
					// Rotate
					Math::mat3{ vec3(std::cos(rad(transform.angle)), std::sin(rad(transform.angle)), 0),
								vec3(-std::sin(rad(transform.angle)), std::cos(rad(transform.angle)), 0),
								vec3(0.f, 0.f, 1.f) }
					*
					// Scale
					Math::mat3{ vec3(s.x, 0, 0),
								vec3(0, s.y, 0),
								vec3(0, 0, 1.f) }
				};

				colliderMat = camMatrix * colliderMat;

				// Set scaled matrix
				GLSLShader::SetUniform("uModel_to_NDC", colliderMat, shd_ref_handle);

				// Draw debug lines
				glLineWidth(5.f);
				glDrawArrays(colliderDebug.primitive_type, 0, colliderDebug.draw_cnt);
				glLineWidth(1.f);

				// unbind VAO and shader program
				glBindVertexArray(0);
				UnUseShaderHandle();
			}
		}
	}
}