/* Start Header**********************************************************************************/
/*
@file    GraphicSystem.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
		 Chia Yi Da		chiayida98@gmail.com
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

#include "Engine/Header/ECS/Coordinator.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"

#include "Engine/Header/Graphic/mesh.hpp"
#include "Engine/Header/Graphic/debugdraw.hpp"
#include "Engine/Header/Graphic/Graphic.hpp"

//#include "Engine/Header/Math/Matrix.hpp"
//#include "../../External Resources/include/stb_image/stb_image.h" //-----remove

namespace Engine {
	extern Coordinator gCoordinator;
	std::shared_ptr<GraphicSystem> GraphicSystem::GS;

	// change GL_TRUE to GL_FALSE to off debug draw, can set this to a key to turn it on and off
	GLboolean GraphicSystem::isDebugDraw = GL_TRUE;
	GLint GraphicSystem::id = 0;

	//GLuint setup_texobj(std::string);
	//GLuint texobj_hdl; //-----remove
	void GraphicSystem::Update(float dt, MathD::Mat3 camMatrix) {
		//For all entities in GraphicSystem

		for (auto const& entity : GS->mEntities) {
			auto& transform = gCoordinator.GetCom<Transform>(entity);
			//Update the matrix (model to ndc)
			//orientation.x += orientation.y * static_cast<GLfloat>(dt);
			/*
			GLfloat rad = MathD::radians(20.f);
			MathD::Mat3 temMat3{ MathD::Vec3(cos(rad), sin(rad), 0),
								 MathD::Vec3(-sin(rad), cos(rad), 0),
								 MathD::Vec3(0, 0, 1.f) };
			*/

			transform.mdl_to_ndc_xform =
				//Translate
				MathD::Mat3{ MathD::Vec3(1.f, 0, 0),
							  MathD::Vec3(0, 1.f, 0),
							  MathD::Vec3(transform.pos.x, transform.pos.y, 1.f) }
				*
				//Scale
				MathD::Mat3{ MathD::Vec3(transform.scale.x, 0, 0),
							 MathD::Vec3(0, transform.scale.y, 0),
							 MathD::Vec3(0, 0, 1.f) };

			//world to ndc * mdl to world
			transform.mdl_to_ndc_xform = camMatrix * transform.mdl_to_ndc_xform;
		}
	}

	void GraphicSystem::Render(MathD::Mat3 camMatrix) {
		GraphicImplementation::BindFramebuffer();

		// Set background to purple color
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//For all entities in GraphicSystem
		for (auto& entity : GS->mEntities) {
			auto& transform = gCoordinator.GetCom<Transform>(entity);
			auto& texture = gCoordinator.GetCom<Texture>(entity);

			// Bind VAO
			glBindVertexArray(transform.mdl_ref->second.vaoid);

			// bind to slot 6
			glBindTextureUnit(6, texture.getTexObj());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


			// Load default shader program
			glUseProgram(GraphicImplementation::shdrpgms["Default"].GetHandle());


			// set uniform variable for texture colour; from slot 6
			GLuint tex_loc = glGetUniformLocation(GraphicImplementation::shdrpgms["Default"].GetHandle(), "uTex2d");
			glUniform1i(tex_loc, 6);
			if (tex_loc == -1) {
				std::cout << "uTex2d variable doesn't exist!!!\n";
				std::exit(EXIT_FAILURE);
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


			// set uniform variable for uModel_to_NDC matrix
			GLint uniform_var_loc1 = glGetUniformLocation(GraphicImplementation::shdrpgms["Default"].GetHandle(), "uModel_to_NDC");
			glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, MathD::value_ptr(transform.mdl_to_ndc_xform));
			if (uniform_var_loc1 == -1) {
				std::cout << "uModel_to_NDC variable doesn't exist!!!\n";
				std::exit(EXIT_FAILURE);
			}

			// Draw Textured object
			glDrawArrays(transform.mdl_ref->second.primitive_type, 0, transform.mdl_ref->second.draw_cnt);

			// unbind VAO and texture
			glBindVertexArray(0);
			texture.Unbind();

			// Unbind default shaders
			GraphicImplementation::shdrpgms["Default"].UnUse();

			// to draw debug lines
			if (isDebugDraw == GL_TRUE) {
				GraphicImplementation::DebugDrawCollider(gCoordinator, entity, transform, camMatrix);
			}
		}
		GraphicImplementation::UnbindFramebuffer();
	}

	bool GraphicSystem::Create(const std::shared_ptr<GraphicSystem>& graphicSystem) {
		GS = graphicSystem;

		//Set up vao for box
		GraphicImplementation::setup_vao();
		GraphicImplementation::setup_shdr();

		LOG_INSTANCE("Graphic System created");
		return true;
	}

	void GraphicSystem::Destroy() {
		LOG_INSTANCE("Graphic System destroyed");
	}

	GraphicSystem::~GraphicSystem() { Destroy(); }


	//
	//// function that sets up the texture object
	//GLuint setup_texobj(std::string filepath) {
	//	GLint width, height, BPP; //BPP - bits per pixel
	//
	//	// flips image in vertically
	//	// OpenGL - Cartesian coordinate system
	//	// PNG - top left
	//	stbi_set_flip_vertically_on_load(1);
	//
	//	// reads and write the width and height into variable, 4 - RBGA
	//	unsigned char* localBuffer = stbi_load(filepath.c_str(), &width, &height, &BPP, 4);
	//
	//	//if (stbi_failure_reason())
	//	//	std::cout << stbi_failure_reason();
	//
	//	// define and initialize a handle to texture object that will
	//	// encapsulate two-dimensional textures
	//	GLuint texobj_hdl;
	//	glCreateTextures(GL_TEXTURE_2D, 1, &texobj_hdl);
	//
	//	// allocate GPU storage for texture image data loaded from file
	//	glTextureStorage2D(texobj_hdl, 1, GL_RGBA8, width, height);
	//
	//	// copy image data from client memory to GPU texture buffer memory
	//	glTextureSubImage2D(texobj_hdl, 0, 0, 0, width, height,
	//		GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	//
	//	// free memory
	//	if (localBuffer)
	//		stbi_image_free(localBuffer);
	//
	//	// nothing more to do - return handle to texture object
	//	return texobj_hdl;
	//





	// utilises collider to draw outer lines
	/*

	// when debugDraw is on
	if (isDebugDraw == GL_TRUE) {
		// when object has collider, get collider matrix
		Collider* col = nullptr;
		if (gCoordinator.HasCom<Collider>(col, entity) && col != nullptr) {
			// set uniform variable for Collider_Matrix matrix
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
				MathD::Mat3{ MathD::Vec3(s.x + 1, 0, 0),
								MathD::Vec3(0, s.y + 1, 0),
								MathD::Vec3(0, 0, 1.f) }
			};

			colliderMat = camMatrix * colliderMat;

			// set collider matrix to slot 1
			GLint uniform_var_loc3 = glGetUniformLocation(transform.shd_ref->second.GetHandle(), "Collider_Matrix");
			glUniformMatrix3fv(uniform_var_loc3, 1, GL_FALSE, MathD::value_ptr(colliderMat));
			if (uniform_var_loc3 == -1) {
				std::cout << "Collider_Matrix variable doesn't exist!!!\n";
				std::exit(EXIT_FAILURE);
			}

			// set uniform variable for uID
			id = 1;
			uniform_var_loc3 = glGetUniformLocation(transform.shd_ref->second.GetHandle(), "uID");
			glUniform1i(uniform_var_loc3, id);
			if (uniform_var_loc3 == -1) {
				std::cout << "uID = 1 variable doesn't exist!!!\n";
				std::exit(EXIT_FAILURE);
			}

			// draw outlines of object
			//glLineWidth(3.f);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDrawArrays(transform.mdl_ref->second.primitive_type, 0, transform.mdl_ref->second.draw_cnt);
		}
	}

	*/
}