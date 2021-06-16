/*
This file has the function definition for class GraphicsSystem
*/

//#include "pch.hpp"

#include "Debug Tools/Logging.hpp"
#include "System/GraphicSystem.hpp"

#include "Coordinator/Coordinator.hpp"
#include "Component/Graphics/TransformComponent.hpp"
#include "Component/Graphics/RendererComponent.hpp"

#include "Graphic/Graphic.hpp"

#include "Math/Matrix.hpp"

extern Coordinator gCoordinator;

//GraphicSystem* GraphicSystem::gs = 0;
//

//
//void GraphicSystem::Destroy() {
//	delete gs;
//}

void GraphicSystem::Update(float dt) {
	//For all entities in PhysicSystem
	
	for (auto const& entity : mEntities) {
		auto& transform = gCoordinator.GetCom<Transform>(entity);
		auto& renderer = gCoordinator.GetCom<Renderer2D>(entity);

		//Update the matrix (model to ndc)
		renderer.mdl_to_ndc_xform = { MathD::Vec3(transform.scale.x, 0, 0), MathD::Vec3(0, transform.scale.y, 0), MathD::Vec3(0, 0, 1.f) };

		//orientation.x += orientation.y * static_cast<GLfloat>(dt);
		GLfloat rad = MathD::radians(transform.rotation);
		MathD::Mat3 temMat3{ MathD::Vec3(cos(rad), sin(rad), 0), MathD::Vec3(-sin(rad), cos(rad), 0), MathD::Vec3(0, 0, 1.f) };
		renderer.mdl_to_ndc_xform = temMat3 * renderer.mdl_to_ndc_xform;
		
		temMat3 = { MathD::Vec3(1.f, 0, 0), MathD::Vec3(0, 1.f, 0), MathD::Vec3(transform.position.x, transform.position.y, 1.f) };
		renderer.mdl_to_ndc_xform = temMat3 * renderer.mdl_to_ndc_xform;

		// world to ndc * mdl to world
		//renderer.mdl_to_ndc_xform = camera2d.world_to_ndc_xform * renderer.mdl_to_ndc_xform;
	}
}

void GraphicSystem::Render() {
	//For all entities in PhysicSystem
	for (auto const& entity : mEntities) {
		auto transform = gCoordinator.GetCom<Transform>(entity);

		/*GLint uniform_var_loc1 = glGetUniformLocation(
			shd_ref->second.GetHandle(), "uModel_to_NDC");
		if (uniform_var_loc1 >= 0) {
			glUniform3fv(uniform_var_loc1, 1,
				glm::value_ptr(transform.));
		}

		else {
			std::cout << "Uniform variable doesn't exist!!!\n";
			std::exit(EXIT_FAILURE);
		}*/
	}
}

bool GraphicSystem::Create() {
	//Set up vao for box
	GraphicImplementation::setup_shdr();
	
	LOG_INSTANCE("Graphic System created");
	return true;
}

void GraphicSystem::Destroy() {
	LOG_INSTANCE("Graphic System destroyed");
}

GraphicSystem::~GraphicSystem() { Destroy();  }