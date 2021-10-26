/* Start Header**********************************************************************************/
/*
@file    DreamECS.cpp
@author  Ow Jian Wen			jianwen.o@digipen.edu
		 Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu
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

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/System/ScriptSystem.hpp"

#define DESTROY_ENTITY(entity_id)\
entityManager->DestroyEntity(entity_id);\
compManager->DestroyEntity(entity_id);
//systemManager->EntityDestroyed(entity);


namespace Engine {
	//Coordinator DreamECS::gCoordinator;
	//std::queue<Entity> DreamECS::destroyQueue;
	// 
	//Track the number of the same name and give index to them
	std::unordered_map <std::string, int> nameCount;

	void DreamECS::Create()
	{
		//gCoordinator.Init();
		compManager = std::make_unique<ComponentManager>();
		entityManager = std::make_unique<EntityManager>();
		//sysManager = std::make_unique<SystemManager>();
	}

	Entity DreamECS::CreateEntity(const char* _entityName, Entity_id _parent) {
		std::string entityName{ _entityName };
		if (nameCount.find(entityName) != nameCount.end()) {
			entityName += std::to_string(nameCount[_entityName]);
			nameCount[_entityName]++;
		}

		else {
			nameCount.insert({ entityName, 1 });
		}

		return entityManager->CreateEntity(entityName.c_str(), _parent);
	}

	void DreamECS::DuplicateEntityAsInstance(Entity entFrom) {
		Entity entTo = entityManager->CreateEntity();
		compManager->DuplicateEntityAsInstance(entFrom.id, entTo.id);
	}

	void DreamECS::DestroyEntity(Entity_id entity_id)
	{
		//destroyQueue.emplace(entity);
		destroySet.insert(entity_id);
	}

	/*const std::vector<Entity>& DreamECS::GetUsedEntitySet() {
		return entityManager->GetUsedEntitySet();
	}*/

	const EntityMapType& DreamECS::GetUsedEntityMap() {
		return entityManager->GetUsedEntityMap();
	}

	uint32_t DreamECS::GetUsedEntitySize() const {
		return entityManager->GetUsedEntitySize();
	}

	void DreamECS::ClearDestroyQueue() {
		
		/*size_t num = destroyQueue.size();
		while (num > 0) {
			Entity& entity = destroyQueue.front();

			DESTROY_ENTITY(entity.id);
			
			destroyQueue.pop();
			--num;
		}*/
		for (auto& entity_id : destroySet) {
			DESTROY_ENTITY(entity_id);
		}

		destroySet.clear();
	}

	void DreamECS::ResetECS() {
		nameCount.clear();

		auto& entityMap = entityManager->GetUsedEntityMap();
		for (auto& [entity_id, entity] : entityMap) {
				//entityManager->DestroyEntity(entity_id);
				compManager->DestroyEntity(entity_id);
		}

		entityManager->ResetEntityManager();
	}

	void DreamECS::Parent(Entity _parent, Entity _child) {

		_child.parent = _parent.id;
		//auto& transChild = GetComponent<TransformComponent>(_child);


	}

	void DreamECS::Unparent(Entity _child) {
		Entity tem = _child;
		_child.parent = DEFAULT_ENTITY_ID;
		auto& transChild = GetComponent<TransformComponent>(_child.id);

		auto size = entityManager->GetUsedEntitySize();
		//auto& vec = entityManager->GetUsedEntitySet();

		/*while (tem.parent != DEFAULT_ENTITY_ID) {
			for (unsigned int i = 0; i < size; i++) {
				if (tem.parent == vec[i].id) {
					transChild += GetComponent<TransformComponent>(vec[i].id);
					tem = vec[i];
				}
			}
		}*/
	}


	void DreamECS::RemoveScript(Entity_id entity_id, const char* className) {
		compManager->RemoveScript(entity_id, className);
	}

}