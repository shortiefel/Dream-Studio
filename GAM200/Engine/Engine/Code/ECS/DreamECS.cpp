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
#include "Engine/Header/ECS/System/TransformCalculationSystem.hpp"
#include "Engine/Header/ECS/Factory.hpp"

#include "Engine/Header/Scene/Prefab.hpp"
#include "Engine/Header/Serialize/GameSceneSerializer.hpp"
#include "Engine/Header/Commands/Command.hpp"
#include "Engine/Header/Commands/ObjectCommand.hpp"

#define DESTROY_ENTITY(entity_id)\
entityManager->DestroyEntity(entity_id);\
compManager->DestroyEntity(entity_id);
//systemManager->EntityDestroyed(entity);

#define DUPLICATE_NAME_CHECK(name) std::string entityName{ name };\
								   if (nameCount.find(entityName) != nameCount.end()) {\
								   		while (nameCount.find(entityName) != nameCount.end()) {\
								   			entityName += std::to_string(nameCount[name]);\
								   			nameCount[name]++;\
								   		}\
								   \
								   		nameCount.insert({ entityName, 1 });\
								   }\
								   \
								   else {\
								   		nameCount.insert({ entityName, 1 });\
								   }

namespace Engine {
	//Coordinator DreamECS::gCoordinator;
	//std::queue<Entity> DreamECS::destroyQueue;
	// 
	//Track the number of the same name and give index to them
	std::unordered_map <std::string, int> nameCount;
	std::unordered_map<Entity_id, Prefab> mapOfPrefab;
	
	std::unordered_set<Entity_id> destroySet{};

	std::unique_ptr<DreamECS> dreamECSGame = std::make_unique<DreamECS>();

	void DreamECS::Create()
	{
		//gCoordinator.Init();
		compManager = std::make_unique<ComponentManager>();
		entityManager = std::make_unique<EntityManager>();
		//sysManager = std::make_unique<SystemManager>();
	}

	Entity& DreamECS::CreateEntity(const char* _entityName, std::unordered_set<Entity_id> _child, Entity_id _parent) {
		DUPLICATE_NAME_CHECK(_entityName);

		return entityManager->CreateEntity(entityName.c_str(), _parent);
	}

	void DreamECS::DuplicateEntityAsInstance(Entity entFrom) {
		DUPLICATE_NAME_CHECK(entFrom.name);
		Entity entTo = entityManager->CreateEntity(entityName.c_str());
		compManager->DuplicateEntityAsInstance(entFrom.id, entTo.id);
	}

	void DreamECS::DestroyEntity(Entity_id entity_id)
	{
		//destroyQueue.emplace(entity);
		destroySet.insert(entity_id);
	}

	void DreamECS::DuplicateNameCheck(std::string& name) {
		DUPLICATE_NAME_CHECK(name);
		name = entityName;
	}

	void DreamECS::ChangeName(std::string _oldname, std::string _newname) {
		nameCount.erase(_oldname);
		nameCount.insert({ _newname, 1 });
	}

	/*const std::vector<Entity>& DreamECS::GetUsedEntitySet() {
		return entityManager->GetUsedEntitySet();
	}*/

	const EntityMapType& DreamECS::GetUsedConstEntityMap() const {
		return entityManager->GetUsedConstEntityMap();
	}

	EntityMapType& DreamECS::GetUsedEntityMap() {
		return entityManager->GetUsedEntityMap();
	}

	uint32_t DreamECS::GetUsedEntitySize() const {
		return entityManager->GetUsedEntitySize();
	}

	const std::unordered_map<Entity_id, Prefab>& DreamECS::GetConstPrefabMap() const {
		return mapOfPrefab;
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

		auto& entityMap = entityManager->GetUsedConstEntityMap();
		for (auto& [entity_id, entity] : entityMap) {
				//entityManager->DestroyEntity(entity_id);
				compManager->DestroyEntity(entity_id);
		}

		entityManager->ResetEntityManager();
	}

	void DreamECS::Parent(Entity_id _parent, Entity_id _child) {
		if (_parent == _child) return;
		if (_parent == DEFAULT_ENTITY_ID) return;
		if (_child == DEFAULT_ENTITY_ID) return;
		TransformCalculationSystem::GetInstance().Parent(_parent, _child);
	}

	void DreamECS::Unparent(Entity_id _target) {
		if (_target == DEFAULT_ENTITY_ID) return;
		TransformCalculationSystem::GetInstance().Unparent(_target);
	}

	void DreamECS::RemoveScript(Entity_id entity_id, const char* className) {
		compManager->RemoveScript(entity_id, className);
	}


	void DreamECS::CreateSquare(Math::vec2 pos, Math::vec2 scale) {
		Factory::InstantiateSquare(pos, scale);
	}

	void DreamECS::CreateCircle(Math::vec2 pos, Math::vec2 scale) {
		Factory::InstantiateCircle(pos, scale);
	}

	void DreamECS::AddPrefab(const Prefab& _prefab) {
		const auto& itr = mapOfPrefab.find(_prefab.entity.id);
		if (itr == mapOfPrefab.end()) {
			mapOfPrefab.emplace(_prefab.entity.id, _prefab);
		}
	}

	void DreamECS::RemovePrefab(const Entity_id& entity_id) {
		const auto& itr = mapOfPrefab.find(entity_id);
		if (itr != mapOfPrefab.end()) {
			mapOfPrefab.erase(itr);
		}
	}

	void DreamECS::UpdateAllPrefab() {
		std::unordered_set<Entity_id> deletePrefabSet;
		auto& entityMap = dreamECSGame->GetUsedEntityMap();
		for (const auto& [id, prefab] : mapOfPrefab) {
			if (entityMap.find(id) == entityMap.end()) {
				deletePrefabSet.emplace(id);
				continue;
			}

			GameSceneSerializer::RefreshPrefab(prefab.prefabName, id);
		}

		for (const auto& id : deletePrefabSet) {
			mapOfPrefab.erase(id);
		}
	}

}