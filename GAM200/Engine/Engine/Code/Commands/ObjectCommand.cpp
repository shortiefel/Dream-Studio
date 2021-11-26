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
#include "Engine/Header/Commands/ObjectCommand.hpp"
#include "Engine/Header/Window.hpp"
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/Graphic/Picking2D.hpp"
#include "Engine/Header/ECS/System/TransformCalculationSystem.hpp"
//#include <ImGuizmo/ImGuizmo.h>
namespace Engine
{
	//void ObjectAddCommand::AddObject(Engine::Entity_id objectid)
	//{
	//	this->object_ID = objectid;
	//}
	bool CheckIfExist(std::map<int, Engine::Entity_id>& entity_selected, Engine::Entity_id _target) {
		for (const auto& [index, entity_id] : entity_selected) {
			if (entity_id == DEFAULT_ENTITY_ID) continue;
			if (entity_id == _target) return true;
		}
		return false;
	}

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
		//		//Engine::dreamECSGame->DestroyEntity(entity_id);
		//		Engine::dreamECSGame->RemoveComponent<Engine::TransformComponent>(entity_id);
		//	}
		//}

		//need entity selected for now its deleting the first one 
		//if (entity_id = true)
		//{
		//	Engine::dreamECSGame->RemoveComponent<Engine::TransformComponent>(entity_id);
		//}
		
		if (entity_selected[0] != DEFAULT_ENTITY_ID)
		{
			Engine::dreamECSGame->DestroyEntity(entity_id);
			Engine::dreamECSGame->RemoveComponent<Engine::TransformComponent>(entity_selected[1]);
		}



	}

	//void ObjectAddCommand::redo()
	//{

	//}

	void ObjectDeleteCommand::execute()
	{

	}

	void ObjectDeleteCommand::undo()
	{
		Engine::dreamECSGame->CreateEntity();
	}

	void ObjectParentCommand::execute()
	{

	}

	void ObjectParentCommand::undo()
	{
		for (const auto& [index, entity_id] : entity_selected) {
			Engine::dreamECSGame->Unparent(entity_id);
		}
	}

	void ObjectGizmoCommand::undo()
	{
		//have yet to add undo for gizmo command
		//Either guizmo or the object picking is being used
		bool guizmoPressed = false;
		//const Engine::Entity_id entity_id = GetTarget(entity_selected);
		//if (!EntityId_Check(entity_id)) {
		//	Engine::TransformComponent* tc = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(entity_id);

		//	if (tc != nullptr) {
		//		ImGuizmo::SetOrthographic(true);
		//		ImGuizmo::SetDrawlist();
		//		ImGuizmo::SetRect(minBound.x, minBound.y, windowSize.x, windowSize.y);
		//		ImGuizmo::SetGizmoSizeClipSpace(EditorSceneCamera::GetHeight() / 4.f);

		//		const Math::mat4 cameraView = EditorSceneCamera::GetTransformMat4();
		//		const Math::mat4 cameraProjection{};

		//		float transArr[3]{ tc->localPosition.x, tc->localPosition.y, 0.f };
		//		float rotArr[3]{ 0.f, 0.f, tc->angle };
		//		float scaleArr[3]{ tc->scale.x, tc->scale.y, 1.f };
		//		Math::mat4 transform;
		//		ImGuizmo::RecomposeMatrixFromComponents(transArr, rotArr, scaleArr, Math::value_ptr(transform));

		//		ImGuizmo::Manipulate(Math::value_ptr(cameraView), Math::value_ptr(cameraProjection),
		//			mCurrentGizmoOperation, ImGuizmo::LOCAL, Math::value_ptr(transform));

		//		if (ImGuizmo::IsUsing()) {
		//			guizmoPressed = true;
		//			ImGuizmo::DecomposeMatrixToComponents(Math::value_ptr(transform), transArr, rotArr, scaleArr);

		//			tc->localPosition = Math::vec2{ transArr[0], transArr[1] };
		//			Engine::TransformCalculationSystem::GetInstance().Update();

		//			float angleDiff = rotArr[2] - tc->angle;
		//			tc->angle += angleDiff;

		//			tc->scale = Math::vec2{ scaleArr[0], scaleArr[1] };

		//			Engine::CommandPtr new_Command = std::make_shared<Engine::ObjectGizmoCommand>();
		//			Engine::UndoRedoManager::GetInstance().StoreCommand(new_Command);
		//		}
		//	}
		//}
	}

	void ObjectGizmoCommand::record()
	{

	}

	void ObjectGizmoCommand::execute()
	{

	}

	void ObjectNameCommand::undo()
	{
		/**
		*	Entity Names
		*/
		if (EntityId_Check(entity_selected)) {
			return;
		}
		auto& entityMap = Engine::dreamECSGame->GetUsedEntityMap();
		if (entityMap.empty()) {
			return;
		}
		const auto& itr = entityMap.find(entity_selected);
		if (itr == entityMap.end()) {
			return;
		}

		std::string& entityName = itr->second.name;
		//char eName[100];
		//strcpy(eName, entityName.c_str());

		//if (Engine::Input::IsKeyPressed(Engine::Input_KeyCode::Enter)) 
		//{
		//		std::string newName = std::string{ eName };
		//		Engine::dreamECSGame->DuplicateNameCheck(newName);
		//		Engine::dreamECSGame->ChangeName(entityName, newName);
		//		entityName = newName;
		//	
		//}
	}


	void ObjectNameCommand::record()
	{

	}

	void ObjectNameCommand::execute()
	{

	}
}