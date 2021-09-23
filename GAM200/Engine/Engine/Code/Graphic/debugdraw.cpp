/* Start Header**********************************************************************************/
/*
@file    debugdraw.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    23/09/2021
\brief
This file contains functions that allows users to draw debug lines for game objects

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Graphic/debugdraw.hpp"

namespace Engine {
	namespace GraphicImplementation {
		void DebugDrawCollider(Coordinator& gCoordinator, Entity const& entity, Transform const& transform, MathD::Mat3 camMatrix) {
			auto& collider = gCoordinator.GetCom<Collider>(entity);
			// when object has collider, get collider matrix
			Collider* col = nullptr;
			if (gCoordinator.HasCom<Collider>(col, entity) && col != nullptr) {

				// Bind VAO
				glBindVertexArray(collider.stencil_ref->second.vaoid);

				// Load stencil shader program
				glUseProgram(GraphicImplementation::shdrpgms["Stencil"].GetHandle());


				// get Collider Matrix
				MathD::Mat3 colliderMat;
				// p = position, s = scale
				MathD::Vec2 p = MathD::Vec2{};
				MathD::Vec2 s = MathD::Vec2{};

				p = col->pos + transform.pos;
				s = col->scale + transform.scale;

				colliderMat = {
					//Translate
					MathD::Mat3{ MathD::Vec3(1.f, 0, 0),
									MathD::Vec3(0, 1.f, 0),
									MathD::Vec3(p.x, p.y, 1.f) }
					*

					//Scale
					MathD::Mat3{ MathD::Vec3(s.x, 0, 0),
									MathD::Vec3(0, s.y, 0),
									MathD::Vec3(0, 0, 1.f) }
				};

				colliderMat = camMatrix * colliderMat;

				// set scaled matrix
				GLint uniform_var_loc3 = glGetUniformLocation(GraphicImplementation::shdrpgms["Stencil"].GetHandle(), "uModel_to_NDC");
				glUniformMatrix3fv(uniform_var_loc3, 1, GL_FALSE, MathD::value_ptr(colliderMat));
				if (uniform_var_loc3 == -1) {
					std::cout << "scaledMatrix variable doesn't exist!!!\n";
					std::exit(EXIT_FAILURE);
				}

				// Draw debug lines
				glLineWidth(5.f);
				glDrawArrays(collider.stencil_ref->second.primitive_type, 0, collider.stencil_ref->second.draw_cnt);
				glLineWidth(1.f);

				// unbind VAO and shader program
				glBindVertexArray(0);
				GraphicImplementation::shdrpgms["Stencil"].UnUse();
			}
		}
	}
}