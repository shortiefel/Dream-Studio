/* Start Header**********************************************************************************/
/*
@file    ObjectCommand.cpp
@author  Goh See Yong, Denise   g.seeyongdenise@digipen.edu
@date    05/11/2021
\brief
This file contain the undo / redo commands for game object/ scene


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/
#include "Engine/Header/Commands/ObjectCommand.hpp"

namespace Engine
{
	void ObjectAddCommand::AddObject(Engine::Entity_id objectid)
	{
		this->object_ID = objectid;
	}

	void ObjectAddCommand::execute()
	{

	}

	void ObjectAddCommand::undo()
	{
		Engine::dreamECSGame->DestroyEntity(object_ID);
	}

}