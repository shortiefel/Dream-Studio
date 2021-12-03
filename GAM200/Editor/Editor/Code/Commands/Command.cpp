/* Start Header**********************************************************************************/
/*
@file    Command.cpp
@author  Goh See Yong, Denise   g.seeyongdenise@digipen.edu	100%
@date    04/11/2021
\brief
This file contain the commands regarding for Undo/Redo System


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/Commands/Command.hpp"

namespace Editor {

	//void Action::StartAction(const Engine::Entity_id* entity)
	//{
	//	auto _entity = entity;
	//	auto transform = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(*_entity);
	//	auto frame = ActionList{ *_entity, *transform };
	//	frames.push(frame);
	//}
	//void Action::UndoAction()
	//{
	//	if (frames.empty()) { return; }

	//	auto lastFrame = frames.top();
	//	auto& transformComp = *Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(lastFrame._entity);
	//	transformComp = lastFrame.trans;
	//	frames.pop();
	//}

	void UndoRedoManager::RecordState(CommandPtr cmd)
	{
		//push the command into undo stack
		undostack.push(cmd);

		//clear redo stack
		redostack = {};

	}

	void UndoRedoManager::Record()
	{
		//get entity data and name
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
		Engine::dreamECSGame->DuplicateNameCheck(entityName);
	}

	void UndoRedoManager::Add(CommandPtr command)
	{
		//Add the newest, current command
		current_command.push_back(command);

		//if the number of commands go over maximum, remove the oldest command
		if (current_command.size() > maximum)
		{
			current_command.pop_front();
		}
	}

	void UndoRedoManager::Undo()
	{
		if (undostack.empty()) { return; }

		//add newest command
		auto cmd = undostack.top();
		undostack.pop();

		cmd->undo();

		redostack.push(cmd);
	}

	void UndoRedoManager::Redo()
	{
		//if nothing to redo then return
		if (redostack.empty()) { return; }

		//get recent command from redo stack
		auto cmd = redostack.top();
		redostack.pop();

		cmd->redo();

		//add command to undo stack
		undostack.push(cmd);

		
	}

	void UndoRedoManager::StoreCommand(CommandPtr command)
	{
		future_command = command;
	}

	CommandPtr UndoRedoManager::GetStoredCommand()
	{
		return future_command;
	}

	void UndoRedoManager::ClearHistory()
	{
		future_command = nullptr;
		undostack = {};
		redostack = {};
	}
}