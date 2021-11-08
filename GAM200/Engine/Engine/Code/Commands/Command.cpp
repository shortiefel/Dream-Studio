/* Start Header**********************************************************************************/
/*
@file    Command.cpp
@author  Goh See Yong, Denise   g.seeyongdenise@digipen.edu
@date    04/11/2021
\brief
This file contain the commands regarding for Undo/Redo System


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Commands/Command.hpp"

namespace Engine {

	void UndoRedoManager::RecordState(CommandPtr cmd)
	{
		//push the command into undo stack
		undostack.push(cmd);

		//clear redo stack
		redostack = {};

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

	//void UndoRedoManager::Redo()
	//{
	//	//if nothing to redo then return
	//	if (redostack.empty()) { return; }

	//	//get recent command from redo stack
	//	auto cmd = redostack.top();
	//	redostack.pop();

	//	cmd->redo();

	//	//add command to undo stack
	//	undostack.push(cmd);
	//}

	void UndoRedoManager::ClearHistory()
	{
		undostack = {};
	}
}