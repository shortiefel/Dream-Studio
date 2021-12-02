/* Start Header**********************************************************************************/
/*
@file    Command.hpp
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

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/Event/MouseEvent.hpp"
#include "Engine/Header/Event/KeyEvent.hpp"
#include "Engine/Header/Event/OverlapColliderEvent.hpp"
#include "Engine/Header/Debug Tools/Profiler.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"
#include "Engine/Header/ECS/Component/ComponentList.hpp"
#include "Engine/Header/Scene/Scene.hpp"

#include <vector>
#include <deque>
#include <stack>
#include <memory>
#include <list>

//#pragma warning(disable:2259)

namespace Editor {

	//the Command Interface
	class ICommand 
	{
	public:
		//execute a command function
		virtual void execute() = 0;

		//undo 
		virtual void undo() = 0;
		
		//redo
		virtual void redo() = 0;
		
		//record state
		virtual void record() = 0;
	
	};

	using CommandPtr = std::shared_ptr<ICommand>;

	//class that knows how to undo and redo user changes
	//template <class T = ICommand>
	class UndoRedoManager : public Engine::Singleton<UndoRedoManager>{
	public:
		
		UndoRedoManager() : maximum(10) {};

		//record current state
		void RecordState(CommandPtr cmd);

		//adding the latest command pointing to the latest command
		void Add(CommandPtr command);
		
		//undo the last command
		void Undo();

		//redo the last command
		void Redo();
		
		//Records last state
		void Record();

		//store command
		void StoreCommand(CommandPtr command);

		//modify the command storing for later
		CommandPtr GetStoredCommand();

		//clear all undo redo histroy
		void ClearHistory();

		//wrap the stack using a std::vector for better performance
		std::deque<CommandPtr> current_command;
		std::deque<CommandPtr> undo_command;

		//testing command list
		//typedef list<T*> CommandList;

		std::stack<CommandPtr> undostack;
		std::stack<CommandPtr> redostack;

		CommandPtr future_command; //for gizmo to store command



	private:
		unsigned int maximum;
		Engine::Entity_id entity_selected;

	};
}

#endif