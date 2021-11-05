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

	class Command 
	{
	public:
		virtual ~Command() {}
		virtual void execute() = 0;
		virtual void undo() = 0;
		virtual void redo() = 0;
		virtual bool merge(Command* other) = 0;
		
		bool CanMerge() const { return _canMerge; }
		bool SetMerge() { return _noMerge; }
		//void UndoCommand();
		//void RedoCommand();

	private:
		static int _id;

	protected:
		bool _canMerge = true;
		bool _noMerge = false;
		
	};
}

#endif