/* Start Header**********************************************************************************/
/*
@file    Command.hpp
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

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Engine/Header/Event/MouseEvent.hpp"
#include "Engine/Header/Event/KeyEvent.hpp"
#include "Engine/Header/Event/OverlapColliderEvent.hpp"
#include "Engine/Header/Debug Tools/Profiler.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"
#include <vector>
#include <deque>
#include <stack>
#include <memory>

#define UNDO true
#define REDO false


namespace Engine {

	class Command : public Singleton<Command>
	{
	typedef std::shared_ptr<Command> CommandPtr;
	public:
		void ExecuteCommand(bool _undo = true);
		virtual void undo() = 0;
		virtual void redo() = 0;
		void UndoCommand();
		void RedoCommand();
		void ClearUndoRedoStack();

	private:
		std::stack<CommandPtr> undo_stack;
		std::stack<CommandPtr> redo_stack;

		CommandPtr _fCommands; //to store a command for future use
		SINGLETON_SETUP(Command);
	};
}

#endif