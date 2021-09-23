/* Start Header**********************************************************************************/
/*
@file    ECSWrapper.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    08/09/2021
\brief
This file is the wrapper file for ECS
-It is made such that in the future the ECS can be changed easily


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/ECSWrapper.hpp"
#include "Engine/Header/ECS/System/ScriptSystem.hpp"


namespace Engine {
	Coordinator DreamECS::gCoordinator;
	std::queue<Entity> DreamECS::destroyQueue;

	void DreamECS::Init()
	{
		gCoordinator.Init();
	}

	Entity DreamECS::CreateEntity()
	{
		return gCoordinator.createEntity();
	}

	void DreamECS::DuplicateEntity(Entity entFrom) {
		Entity entTo = gCoordinator.createEntity();
		gCoordinator.DuplicateEntity(entFrom, entTo);

		/*const auto& listOfClassInstance = ScriptSystem::csEntityClassInstance.find(entFrom)->second;
		CSClassInstance newClassInstance;
		for (auto& [className, scriptInstance] : listOfClassInstance) {
			newClassInstance.emplace(className, CSScriptInstance{ className });
		}

		ScriptSystem::csEntityClassInstance.emplace(entTo, std::move(newClassInstance));*/
	}

	void DreamECS::DestroyEntity(Entity entity)
	{
		//gCoordinator.destroyEntity(entity);
		destroyQueue.emplace(entity);
	}

	const std::unordered_set<Entity>& DreamECS::GetUsedEntitySet() {
		return gCoordinator.GetUsedEntitySet();
	}

	void DreamECS::ClearDestroyQueue() {
		//std::cout << gCoordinator.GetUsedEntitySet().size() << "\n";
		size_t num = destroyQueue.size();
		while (num > 0) {
			Entity& entity = destroyQueue.front();
			gCoordinator.destroyEntity(entity);
			//ScriptSystem::csEntityClassInstance.erase(entity);
			destroyQueue.pop();
			--num;
		}
	}

	void DreamECS::ResetECS() {
		std::unordered_set<Entity> listOfEntity = gCoordinator.GetUsedEntitySet();
		for (auto& entity : listOfEntity) {
			gCoordinator.destroyEntity(entity);
		}

		gCoordinator.ResetECS();
	}

}