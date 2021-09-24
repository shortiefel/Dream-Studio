/* Start Header**********************************************************************************/
/*
@file    debugdraw.cpp
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

#include "Engine/Header/Graphic/debugdraw.hpp"
#include "Engine/Header/Graphic/GraphicOptions.hpp"

#include "Engine/Header/ECS/ECSWrapper.hpp"

namespace Engine {
	namespace GraphicImplementation {
		void DebugDrawCollider(Entity const& entity, Transform const& transform, Math::mat3 camMatrix) {
			Collider* collider = DreamECS::GetComponentTest<Collider>(entity);
			// when object has collider, get collider matrix
			//Collider* col = nullptr;
			if (collider != nullptr) {

				// Bind VAO
				auto colliderStencil = GraphicImplementation::models[GraphicShape::STENCIL];
				glBindVertexArray(colliderStencil.vaoid);

				// Load stencil shader program
				glUseProgram(GraphicImplementation::shdrpgms[GraphicShader::STENCIL].GetHandle());


				// p = position, s = scale
				Math::vec2 p = collider->offset_position + transform.position;
				Math::vec2 s = collider->offset_scale * transform.scale;

				// get Collider Matrix
				Math::mat3 colliderMat = {
					//Translate
					Math::mat3{ Math::vec3(1.f, 0, 0),
									Math::vec3(0, 1.f, 0),
									Math::vec3(p.x, p.y, 1.f) }
					*
					Math::mat3{ Math::vec3(std::cos(Math::radians((float)transform.angle)), std::sin(Math::radians((float)transform.angle)), 0),
								  Math::vec3(-std::sin(Math::radians((float)transform.angle)), std::cos(Math::radians((float)transform.angle)), 0),
								  Math::vec3(0.f, 0.f, 1.f) }
					*

					//Scale
					Math::mat3{ Math::vec3(s.x, 0, 0),
									Math::vec3(0, s.y, 0),
									Math::vec3(0, 0, 1.f) }
				};

				colliderMat = camMatrix * colliderMat;

				// set scaled matrix
				GLint uniform_var_loc3 = glGetUniformLocation(GraphicImplementation::shdrpgms[GraphicShader::STENCIL].GetHandle(), "uModel_to_NDC");
				glUniformMatrix3fv(uniform_var_loc3, 1, GL_FALSE, Math::value_ptr(colliderMat));
				if (uniform_var_loc3 == -1) {
					std::cout << "scaledMatrix variable doesn't exist!!!\n";
					std::exit(EXIT_FAILURE);
				}

				// Draw debug lines
				glLineWidth(5.f);
				glDrawArrays(colliderStencil.primitive_type, 0, colliderStencil.draw_cnt);
				glLineWidth(1.f);

				// unbind VAO and shader program
				glBindVertexArray(0);
				GraphicImplementation::shdrpgms[GraphicShader::STENCIL].UnUse();
			}
		}
	}
}