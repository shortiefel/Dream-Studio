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
		//---------------------------------------------------------------------------------------------------------------
		//Using
		void ObjectTransformChangeCommand::undo()
		{
			Engine::TransformComponent* tc = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(prevTransform.GetEntityId());
			if (tc != nullptr) *tc = prevTransform;
			std::cout << "Undo " << prevTransform.position << " " << prevTransform.GetEntityId() << "\n";
		}

		void ObjectTransformChangeCommand::redo()
		{
			Engine::TransformComponent* tc = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(nextTransform.GetEntityId());
			if (tc != nullptr) *tc = nextTransform;
			std::cout << "Redo " << nextTransform.position << " " << nextTransform.GetEntityId() << "\n";
		}

		void ObjectTransformChangeCommand::record()
		{

		}

		void ObjectTransformChangeCommand::execute()
		{

		}

		ObjectTransformChangeCommand::ObjectTransformChangeCommand(Engine::TransformComponent _prevTransform, Engine::TransformComponent _nextTransform) :
			prevTransform { _prevTransform }, nextTransform{ _nextTransform } {
			std::cout << prevTransform.GetEntityId() << " " << _nextTransform.GetEntityId() << "\n";
		}
		//---------------------------------------------------------------------------------------------------------------
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

	void ObjectTransformCommand::SetOldPosition(Engine::DreamMath::vec2 _oldPosition)
	{
		_oldposition = _oldPosition;
	}


	void ObjectTransformCommand::SetNewPosition(Engine::DreamMath::vec2 _newPosition)
	{
		_newposition = _newPosition;
	}
	//void ObjectTransformCommand::SetOldPosition(unsigned int* _id)
	//{
	//	_oldposition =_id;
	//}

	//void ObjectTransformCommand::SetNewPosition(unsigned int* _id)
	//{
	//	_newposition = _id;
	//}

	//void ObjectTransformCommand::StoredTransform(std::map<int, Engine::Entity_id>& entity_selected, Engine::DreamMath::vec2 positions)
	void ObjectTransformCommand::StoredTransform(Engine::Entity_id entity_id, Engine::DreamMath::vec2 positions)
	{
		positions = Engine::dreamECSGame->GetComponent<Engine::TransformComponent>(entity_id).position;
		Engine::TransformComponent* id_transform = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(entity_id);
		if (id_transform != nullptr)
		{
			id_transform->position = positions;
			id_transform->localPosition = positions;
			Engine::ParentManager::GetInstance().UpdateTruePos(entity_id);

		}

		//Engine::TransformComponent * transform = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(GetTarget(entity_selected));
		//auto& transform = Engine::dreamECSGame->GetComponent<Engine::TransformComponent>(GetTarget(entity_selected));
		//auto& entityMap = Engine::dreamECSGame->GetUsedConstEntityMap();
		
		//std::cout << "printing out"<< "\n";
		/*transform.position = positions - Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(GetTarget(entity_selected))->position;
		transform.localPosition = positions - Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(GetTarget(entity_selected))->localPosition;*/
		//Engine::ParentManager::GetInstance().UpdateTruePos(entity_id);
		 



		//this one affects all entity but after that will be able to undo each entity
		//auto& transformArray = Engine::dreamECSGame->GetComponentArrayData<Engine::TransformComponent>();
		//auto& entity_map = Engine::dreamECSGame->GetUsedConstEntityMap();

		//for (auto& [id, entity] : entity_map) {
		//	
		//	bool selected = CheckIfExist(entity_selected, id);
		//	std::cout << id << "\n";
		//	
		//	if (Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(id) != nullptr)
		//	{
		//		if (selected)
		//		{
		//			std::cout << "not printing out" << "\n";
		//			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 255, 255));
		//			Engine::TransformComponent* transform = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(id);
		//			//Engine::DreamECS::GetComponent<>(id);
		//			transform->position = positions;
		//			transform->localPosition = positions;
		//			Engine::ParentManager::GetInstance().UpdateTruePos(id);
		//		}
		//		else
		//		{
		//			std::cout << "hello im here \n";
		//			Engine::ParentManager::GetInstance().UpdateTruePos(id);
		//		}
		//	}

		//}

	

	}

	void ObjectTransformCommand::undo()
	{
		std::cout << " past undo-ing" << "\n";
		//StoredTransform(id, _position);
		//StoredTransform(entity_selected, _oldposition);
	}

	void ObjectTransformCommand::redo()
	{
		std::cout << "redo ing" << "\n";
		//StoredTransform(entity_selected, _newposition);
	}

	void ObjectTransformCommand::record()
	{

	}

	void ObjectTransformCommand::execute()
	{

	}



	void ObjectDeleteCommand::undo()
	{
		Engine::dreamECSGame->DuplicateEntityAsInstance(object_ID);
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