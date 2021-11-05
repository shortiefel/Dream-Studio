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
	void ObjectAddState::SetOldScene(std::string oldScene)
	{
		currentScene = new Scene{ oldScene };
		Engine::GameSceneSerializer::SerializeScene(oldScene);
	}

	void ObjectAddState::SetNewScene(std::string newScene)
	{
		currentScene->Stop(false);
		currentScene = new Scene{ newScene };
		Engine::GameSceneSerializer::SerializeScene(newScene);
	}

	void ObjectAddState::undo()
	{
		if (!commands.empty())
		{
			commands.top()->undo();
			commands.pop();
		}
	}
}