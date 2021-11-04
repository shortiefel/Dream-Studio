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

#define UNDO true
#define REDO false


namespace Engine {

	class Command 
	{
		void ExecuteCommand(bool _undo = true);
		void UndoCommand();
		void RedoCommand();
	};
}

#endif