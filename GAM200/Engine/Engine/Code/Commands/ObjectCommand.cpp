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
		auto& entity_map = Engine::dreamECSGame->GetUsedConstEntityMap();
		for (auto& [id, entity] : entity_map)
		{
			bool selected = CheckIfExist(entity_selected, id);
			if (selected)
			{
				//Engine::dreamECSGame->DestroyEntity(entity_id);
				Engine::dreamECSGame->RemoveComponent<Engine::TransformComponent>(entity_id);
			}
		}
		//if (entity_id = true)
		//{
		//	Engine::dreamECSGame->DestroyEntity(entity_id);
		//	Engine::dreamECSGame->RemoveComponent<Engine::TransformComponent>(entity_id);
		//}




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
}