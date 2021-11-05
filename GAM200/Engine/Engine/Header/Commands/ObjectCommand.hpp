/* Start Header**********************************************************************************/
/*
@file    ObjectCommand.hpp
@author  Goh See Yong, Denise   g.seeyongdenise@digipen.edu
@date    04/11/2021
\brief
This file contain the undo / redo commands for game object


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef OBJECT_COMMAND_HPP
#define OBJECT_COMMAND_HPP

#include "Engine/Header/Commands/Command.hpp"

namespace Engine {
	class ObjectCommand : public ICommand
	{
	public:
		void undo() override;

		//voir redo() ovverride;
	};
}
#endif
