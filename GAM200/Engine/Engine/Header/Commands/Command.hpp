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
#include "Engine/Header/ECS/Component/ComponentList.hpp"
#include "Engine/Header/Scene/Scene.hpp"

#include <vector>
#include <deque>
#include <stack>
#include <memory>



namespace Engine {

	//the Command Interface
	class ICommand 
	{
	public:
		
		//execute a command function
		virtual void execute() = 0;

		//undo 
		virtual void undo() = 0;
		//virtual void redo() = 0;
	
	};

	using CommandPtr = std::shared_ptr<ICommand>;

	//class that knows how to undo and redo user changes
	class UndoRedoManager : public Singleton<UndoRedoManager>{
	public:
		
		UndoRedoManager() : maximum(10) {};

		//adding the latest command pointing to the latest command
		void Add(CommandPtr command);
		//undo the last command
		void Undo();
		//redo the last command
		//void Redo();

		//store command to do next time
		
		//clear all undo redo histroy
		void ClearHistory();


		//wrap the stack using a std::vector for better performance
		std::deque<CommandPtr> current_command;
		std::deque<CommandPtr> undo_command;

		std::stack<CommandPtr> undostack;
		std::stack<CommandPtr> redostack;



	private:
		unsigned int maximum;

	};
}

#endif