/* Start Header**********************************************************************************/
/*
@file    TransformCalculationSystem.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    28/10/2021
@brief
This file has the class definition to manage: TransformCalculationSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/System/TransformCalculationSystem.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/ComponentArray.hpp"




namespace Engine {
	/*TrueTransformMap trueTransform;

	TrueTransformMap& TransformCalculationSystem::GetTrueTransformMap() {
		return trueTransform;
	}*/

	/*void TransformCalculationSystem::SetTrueTransform(Entity_id _idx, Math::vec2 _position) {
		trueTransform[_idx].position = _position;
	}*/

	void TransformCalculationSystem::Update() {
		auto& transformArray = dreamECSGame->GetComponentArrayData<TransformComponent>();
		auto& entityMap = dreamECSGame->GetUsedConstEntityMap();

		for (auto& transform : transformArray) {
			const Entity_id& entity_id = transform.GetEntityId();
			if (EntityId_Check(entity_id)) break;

			const auto& itr = entityMap.find(entity_id);
			Entity_id parent = itr->second.parent;

			transform.position = transform.localPosition;
			if (parent != DEFAULT_ENTITY_ID) {
				transform.position += dreamECSGame->GetComponent<TransformComponent>(parent).localPosition;
			}
		}
	}

	void TransformCalculationSystem::ChildUpdate() {
		auto& transformArray = dreamECSGame->GetComponentArrayData<TransformComponent>();
		auto& entityMap = dreamECSGame->GetUsedConstEntityMap();

		for (auto& transform : transformArray) {
			const Entity_id& entity_id = transform.GetEntityId();
			if (EntityId_Check(entity_id)) break;

			const auto& itr = entityMap.find(entity_id);
			Entity_id parent = itr->second.parent;

			if (parent != DEFAULT_ENTITY_ID) {
				transform.position = transform.localPosition + dreamECSGame->GetComponent<TransformComponent>(parent).position;
			}
		}
	}

	void TransformCalculationSystem::Release() {
		auto& transformArray = dreamECSGame->GetComponentArrayData<TransformComponent>();
		auto& entityMap = dreamECSGame->GetUsedConstEntityMap();

		for (auto& transform : transformArray) {
			const Entity_id& entity_id = transform.GetEntityId();
			if (EntityId_Check(entity_id)) break;

			const auto& itr = entityMap.find(entity_id);
			Entity_id parent = itr->second.parent;

			transform.localPosition = transform.position;
			if (parent != DEFAULT_ENTITY_ID) {
				transform.localPosition -= dreamECSGame->GetComponent<TransformComponent>(parent).position;
			}
		}
	}

	void TransformCalculationSystem::Parent(Entity_id _parent, Entity_id _child) {
		auto& entityMap = dreamECSGame->GetUsedEntityMap();
		auto& childEntity = entityMap[_child];
		if (childEntity.parent == _parent) return;

		entityMap[_parent].child.emplace(_child);
		entityMap[_child].parent = _parent;
		TransformComponent* itr = dreamECSGame->GetComponentPTR<TransformComponent>(_child);
		if (itr == nullptr) return;
		auto& pos = itr->localPosition;
		TransformComponent* itr2 = dreamECSGame->GetComponentPTR<TransformComponent>(_parent);
		if (itr2 == nullptr) return;
		pos -= itr2->position;
	}

	void TransformCalculationSystem::Unparent(Entity_id _target) {
		auto& entityMap = dreamECSGame->GetUsedEntityMap();
		Entity_id& parent = entityMap[_target].parent;
		if (parent == DEFAULT_ENTITY_ID) return;

		Entity& parentEntity = entityMap[parent];
		const auto& itr = parentEntity.child.find(_target);
		if (itr != parentEntity.child.end()) {
			parentEntity.child.erase(itr);
		}
		
		auto& pos = dreamECSGame->GetComponent<TransformComponent>(_target).localPosition;
		pos += dreamECSGame->GetComponent<TransformComponent>(parent).position;

		parent = DEFAULT_ENTITY_ID;
	}

	bool TransformCalculationSystem::Create() {
		LOG_INSTANCE("TransformCalculationSystem System created");
		return true;
	}

	void TransformCalculationSystem::Destroy() {
		LOG_INSTANCE("TransformCalculationSystem System destroyed");
	}
}
