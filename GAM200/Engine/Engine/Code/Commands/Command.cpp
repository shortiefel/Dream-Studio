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

	void Command::UndoCommand()
	{
		//if nothing to undo 
		if (undo_stack.empty()) { return; }

		//get the most recent command 
		auto command = undo_stack.top();
		undo_stack.pop();

		redo_stack.push(command);
	}
	void Command::RedoCommand()
	{
		//if nothing to undo 
		if (redo_stack.empty()) { return; }

		//get the most recent command 
		auto command = redo_stack.top();
		redo_stack.pop();

		undo_stack.push(command);
	}
}