/* Start Header**********************************************************************************/
/*
@file    CommandHistory.hpp
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

#ifndef COMMAND_HISTORY_HPP
#define COMMAND_HISTORY_HPP

#include "Engine/Header/Commands/Command.hpp"

namespace Engine {
	
	class CommandHistory
	{
	public:
		static void AddCommand(Command* cmd);
		static void UndoCommand();
		static void RedoCommand();


	private:
		static Command* _commands[1000];
		static int _commandsize;
		static int _commandptr;
	};
}
#endif 
