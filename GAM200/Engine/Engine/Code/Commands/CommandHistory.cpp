/* Start Header**********************************************************************************/
/*
@file    CommandHistory.cpp
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
#include "Engine/Header/Commands/CommandHistory.hpp"

namespace Engine {

	Command* CommandHistory::_commands[1000] = {};
	int CommandHistory::_commandsize = 0;
	int CommandHistory::_commandptr = 0;

	void CommandHistory::AddCommand(Command* cmd)
	{
		cmd->execute();

		if (_commandptr < _commandsize - 1)
		{
			for (int i = _commandsize - 1; i > _commandptr; i--)
			{
				delete _commands[i];
			}
			_commandsize = _commandptr + 1;
		}

		_commands[_commandsize] = cmd;
		_commandsize++;

		if (_commandsize > 1 && _commands[_commandsize - 1]->CanMerge() && _commands[_commandsize - 2]->CanMerge())
		{
			if (_commands[_commandsize - 1]->merge(_commands[_commandsize - 2]))
			{
				delete _commands[_commandsize - 1];
				_commandsize--;
			}
		}

		_commandptr = _commandsize - 1;
	}

	void CommandHistory::UndoCommand()
	{
		if (_commandptr >= 0)
		{
			_commands[_commandptr]->undo();
			_commandptr--;
		}
	}

	void CommandHistory::RedoCommand()
	{
		int redo_command = _commandptr + 1;
		if (redo_command < _commandsize && redo_command >= 0)
		{
			_commands[redo_command]->execute();
			_commandptr++;
		}
	}
}