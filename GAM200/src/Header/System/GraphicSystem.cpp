/* Start Header**********************************************************************************/
/*
@file    GraphicSystem.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
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

#include "Debug Tools/Logging.hpp"
#include "System/GraphicSystem.hpp"
#include "System/CameraSystem.hpp"

#include "Coordinator/Coordinator.hpp"
#include "Component/Graphics/TransformComponent.hpp"
#include "Component/Graphics/RendererComponent.hpp"
#include "Component/Graphics/TextureComponent.hpp"

#include "Graphic/Graphic.hpp"

#include "Math/Matrix.hpp"

extern Coordinator gCoordinator;
std::shared_ptr<GraphicSystem> GraphicSystem::GS;

GLuint setup_texobj(std::string);

void GraphicSystem::Update(float dt) {
	//For all entities in GraphicSystem
	
	for (auto const& entity : GS->mEntities) {
		auto& transform = gCoordinator.GetCom<Transform>(entity);
		auto& renderer = gCoordinator.GetCom<Renderer2D>(entity);

		//Update the matrix (model to ndc)
		renderer.mdl_to_ndc_xform = { MathD::Vec3(transform.scale.x, 0, 0), 
									  MathD::Vec3(0, transform.scale.y, 0),
									  MathD::Vec3(0, 0, 1.f) };

		//orientation.x += orientation.y * static_cast<GLfloat>(dt);
		GLfloat rad = MathD::radians(transform.rotation);
		MathD::Mat3 temMat3{ MathD::Vec3(cos(rad), sin(rad), 0), 
							 MathD::Vec3(-sin(rad), cos(rad), 0), 
							 MathD::Vec3(0, 0, 1.f) };

		renderer.mdl_to_ndc_xform = temMat3 * renderer.mdl_to_ndc_xform;
		
		temMat3 = { MathD::Vec3(1.f, 0, 0), 
					MathD::Vec3(0, 1.f, 0), 
					MathD::Vec3(transform.pos.x, transform.pos.y, 1.f) };

		renderer.mdl_to_ndc_xform = temMat3 * renderer.mdl_to_ndc_xform;

		// world to ndc * mdl to world
		renderer.mdl_to_ndc_xform = CameraSystem::GetTransform() * renderer.mdl_to_ndc_xform;
	}
}

void GraphicSystem::Render() {
	//For all entities in PhysicSystem
	for (auto const& entity : GS->mEntities) {
		auto& transform = gCoordinator.GetCom<Transform>(entity);
		auto& renderer = gCoordinator.GetCom<Renderer2D>(entity);

		glBindVertexArray(renderer.mdl_ref->second.vaoid);

		// leaving it here atm, need to change to texture tag with model(?)
		// have not call ~texture() yet
		// frames super low, (no texture > test2 > test1) 
		// assumption is bc of doing texture loading in render
		Texture texture("Assets/Textures/test2.png");
		texture.Bind(6);

		// load shader program in use by this object
		renderer.shd_ref->second.Use();

		GLuint tex_loc = glGetUniformLocation(renderer.shd_ref->second.GetHandle(), "uTex2d");
		glUniform1i(tex_loc, 6);
		if (tex_loc == -1) {
			std::cout << "uTex2d variable doesn't exist!!!\n";
			std::exit(EXIT_FAILURE);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// bind VAO of this object's model
		glBindVertexArray(renderer.mdl_ref->second.vaoid);
		
		GLint uniform_var_loc1 = glGetUniformLocation(renderer.shd_ref->second.GetHandle(), "uModel_to_NDC");
		glUniformMatrix3fv(uniform_var_loc1, 1, GL_FALSE, MathD::value_ptr(renderer.mdl_to_ndc_xform));
		if (uniform_var_loc1 == -1) {
			std::cout << "uModel_to_NDC variable doesn't exist!!!\n";
			std::exit(EXIT_FAILURE);
		}

		//glDrawElements(mdl_ref->second.primitive_type, mdl_ref->second.draw_cnt, GL_UNSIGNED_SHORT, NULL);
		glDrawArrays(renderer.mdl_ref->second.primitive_type, 0, renderer.mdl_ref->second.draw_cnt);

		// unbind VAO and unload shader program
		texture.Unbind();
		glBindVertexArray(0);
		renderer.shd_ref->second.UnUse();
	}
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
//}