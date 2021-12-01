/* Start Header**********************************************************************************/
/*
@file    ObjectCommand.cpp
@author  Goh See Yong, Denise   g.seeyongdenise@digipen.edu	100%
@date    05/11/2021
\brief
This file contain the undo / redo commands for game object/ scene


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/Commands/ObjectCommand.hpp"

#include "Engine/Header/Window.hpp"
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/Graphic/Picking2D.hpp"
#include "Engine/Header/ECS/System/TransformCalculationSystem.hpp"
#include "Engine/Header/Parent/ParentManager.hpp"
#include "Engine/Header/Input/Input.hpp"

//#include <ImGuizmo/ImGuizmo.h>
#include <Imgui/imgui.h>

namespace Editor
{
	namespace GUI_Windows {
	//void ObjectAddCommand::AddObject(Engine::Entity_id objectid)
	//{
	//	this->object_ID = objectid;
	//}

	void ObjectAddCommand::execute()
	{

	}

	void ObjectAddCommand::record()
	{

	}

	void ObjectAddCommand::undo()
	{
		//undo for entity
		//if (!object_ID)
		//{
		//Engine::dreamECSGame->DestroyEntity(object_ID);
		//
		//std::for_each(entity_selected.begin(), entity_selected.end(), [](std::pair<int, Engine::Entity_id> entity) { Engine::dreamECSGame->DestroyEntity(entity.second);  });
		//entity_selected.clear();
		//}

		//undo for component 
		// if selected then will remove the object
		//if entity is selected = true then undo
		//auto& entity_map = Engine::dreamECSGame->GetUsedConstEntityMap();
		//for (auto& [id, entity] : entity_map)
		//{
		//	bool selected = CheckIfExist(entity_selected, id);
		//	if (selected)
		//	{
		//		if (Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(id) == nullptr) {
		//			//if (entity.child.empty()) {
		//			if (selected)
		//				ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255));

		//			if (ImGui::Selectable(entity.name.c_str()))
		//			{
		//				ClickCheck(entity_selected, id);

		//			}
		//
		//			if (selected)
		//				ImGui::PopStyleColor();

		//		}
		//		Engine::dreamECSGame->RemoveComponent<Engine::TransformComponent>(entity_id);
		//	}
		//}

		if (entity_selected[0] != DEFAULT_ENTITY_ID)
		{
			Engine::Entity_id selected = GetTarget(entity_selected);
			Engine::dreamECSGame->RemoveComponent<Engine::TransformComponent>(selected);
		}




	}

	void ObjectAddCommand::redo()
	{
		Engine::TransformComponent* transform = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(GetTarget(entity_selected));
		if (transform != nullptr)
		{
			Engine::dreamECSGame->AddComponent<Engine::TransformComponent>(GetTarget(entity_selected));

		}
	}


	Engine::DreamMath::vec2 ObjectTransformCommand::GetTransformPosition()
	{
		return _position;
	}

	void ObjectTransformCommand::StoredTransform(Engine::Entity_id _id, Engine::DreamMath::vec2 positions)
	{
		positions = GetTransformPosition();
		/*Engine::TransformComponent* entity_transform = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(_id);*/
		//Engine::TransformComponent* id_transform = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(_id);
		//if (id_transform != nullptr)
		//{
		//	if (EntityId_Check(_id)) {
		//		return;
		//	}
		//	id_transform->position =  positions;
		//	id_transform->localPosition = positions;
		//	Engine::ParentManager::GetInstance().UpdateTruePos(_id);

		//}

		//this one affects all entity but after that will be able to undo each entity
		auto& transformArray = Engine::dreamECSGame->GetComponentArrayData<Engine::TransformComponent>();
		auto& entityMap = Engine::dreamECSGame->GetUsedConstEntityMap();

		for (auto& transform : transformArray) {
			_id = transform.GetEntityId();
			if (EntityId_Check(_id)) break;

			const auto& itr = entityMap.find(_id);
			Engine::Entity_id parent = itr->second.parent;

			transform.position = transform.localPosition;
			transform.position = positions;
			transform.localPosition = positions;

			if (parent != DEFAULT_ENTITY_ID) {
				transform.position += Engine::dreamECSGame->GetComponent<Engine::TransformComponent>(parent).localPosition;
			}
		}

	}

	void ObjectTransformCommand::undo()
	{
		_oldposition = GetTransformPosition();
		StoredTransform(id, _oldposition);
	}

	void ObjectTransformCommand::redo()
	{
		std::cout << "redo ing" << "\n";
		_newposition = 10.0f;
		StoredTransform(id, _newposition);
	}

	void ObjectTransformCommand::record()
	{

	}

	void ObjectTransformCommand::execute()
	{

	}



	void ObjectDeleteCommand::undo()
	{
		Engine::dreamECSGame->CreateEntity();
	}

	void ObjectDeleteCommand::redo()
	{

	}

	void ObjectDeleteCommand::execute()
	{

	}

	void ObjectParentCommand::undo()
	{
		for (const auto& [index, entity_id] : entity_selected) {
			Engine::dreamECSGame->Unparent(entity_id);
		}
	}

	void ObjectParentCommand::execute()
	{

	}
	}



}