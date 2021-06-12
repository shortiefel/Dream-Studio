/*
This file has the function definition for class GraphicsSystem
*/

#include "Debug Tools/Logging.hpp"
#include "System/GraphicSystem.hpp"
#include "Coordinator/Coordinator.hpp"
#include "Component/Graphics/TransformComponent.hpp"

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
		auto transform = gCoordinator.GetCom<Transform>(entity);

		//Update the matrix (model to ndc)

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
	
	LOG_INSTANCE("Graphic System created");
	return true;
}

void GraphicSystem::Destroy() {
	LOG_INSTANCE("Graphic System destroyed");
}

GraphicSystem::~GraphicSystem() { Destroy();  }