/* Start Header**********************************************************************************/
/*
@file    GraphicSystem.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/ComponentArray.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"

#include "Engine/Header/Graphic/mesh.hpp"
#include "Engine/Header/Graphic/shader.hpp"
#include "Engine/Header/Graphic/glslshader.hpp"

#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/Graphic/GraphicOptions.hpp"
#include "Engine/Header/Graphic/debugdraw.hpp"

namespace Engine {

	void GraphicSystem::Render(Math::mat3 camMatrix) {
		GraphicImplementation::BindFramebuffer();

		// Set background to purple color
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Check texture because less Texture component on entity than Transform
		const auto& textureArray = DreamECS::GetInstance().GetComponentArrayData<TextureComponent>();
		for (const auto& texture : textureArray) {
			const Entity& entity = texture.GetEntity();
			if (Entity_Check(entity)) break;
			if (!texture.isActive) continue;

			TransformComponent* transform = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(entity);
			if (!transform || !transform->isActive) continue;

			const auto& mdl_ref = GraphicImplementation::models[texture.mdl_ref];

			glBindVertexArray(mdl_ref.vaoid);
			glBindTextureUnit(6, texture.texobj_hdl);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			// Load shader program
			const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::DEFAULT].GetHandle();
			GraphicImplementation::UseShaderHandle(shd_ref_handle);

			GLSLShader::SetUniform("uTex2d", 6, shd_ref_handle);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			GLSLShader::SetUniform("uModel_to_NDC", camMatrix * transform->GetTransform(), shd_ref_handle);

			//glDrawElements(mdl_ref.primitive_type, mdl_ref.draw_cnt, GL_UNSIGNED_SHORT, NULL);
			glDrawArrays(mdl_ref.primitive_type, 0, mdl_ref.draw_cnt);

			// unbind VAO and unload shader program
			texture.Unbind();
			glBindVertexArray(0);

			// unload shader program
			GraphicImplementation::UnUseShaderHandle();

			// to draw debug lines
			if (isDebugDraw == GL_TRUE) {
				GraphicImplementation::DebugDrawCollider(entity, *transform, camMatrix);
			}
		}
		
		GraphicImplementation::UnbindFramebuffer();
	}

	//bool GraphicSystem::Create(const std::shared_ptr<GraphicSystem>& graphicSystem) {
	bool GraphicSystem::Create() {
		//GS = graphicSystem;

		//Set up vao for box
		GraphicImplementation::setup_vao();
		GraphicImplementation::setup_shdr();

		LOG_INSTANCE("Graphic System created");
		return true;
	}

	void GraphicSystem::Destroy() {
		LOG_INSTANCE("Graphic System destroyed");
	}

	//GraphicSystem::~GraphicSystem() { Destroy(); }


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
			Math::mat3 colliderMat;

			// p = position, s = scale
			Math::vec2 p = Math::vec2{};
			Math::vec2 s = Math::vec2{};

			p = col->pos + transform.pos;
			s = col->scale + transform.scale;

			colliderMat = {
				//Translate
				Math::mat3{ Math::vec3(1.f, 0, 0),
								Math::vec3(0, 1.f, 0),
								Math::vec3(p.x, p.y, 1.f) }
				*

				//Scale
				Math::mat3{ Math::vec3(s.x + 1, 0, 0),
								Math::vec3(0, s.y + 1, 0),
								Math::vec3(0, 0, 1.f) }
			};

			colliderMat = camMatrix * colliderMat;

			// set collider matrix to slot 1
			GLint uniform_var_loc3 = glGetUniformLocation(transform.shd_ref->second.GetHandle(), "Collider_Matrix");
			glUniformMatrix3fv(uniform_var_loc3, 1, GL_FALSE, Math::value_ptr(colliderMat));
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