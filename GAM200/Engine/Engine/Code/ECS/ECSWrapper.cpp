
#include "Engine/Header/ECS/ECSWrapper.hpp"


namespace Engine {
	Coordinator DreamECS::gCoordinator;


	Coordinator& DreamECS::GetCoordinator() { return gCoordinator; }

	Entity DreamECS::CreateEntity()
	{
		return gCoordinator.createEntity();
	}

	void DreamECS::DestroyEntity(Entity entity)
	{
		gCoordinator.destroyEntity(entity);
	}

	void DreamECS::DestroyAllEntity()
	{
		gCoordinator.destroyAllEntity();
	}

	const std::vector<Entity>& DreamECS::GetUsedEntityVector() {
		return gCoordinator.GetUsedEntityVector();
	}

}