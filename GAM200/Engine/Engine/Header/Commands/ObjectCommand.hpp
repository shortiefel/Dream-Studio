/* Start Header**********************************************************************************/
/*
@file    ObjectCommand.hpp
@author  Goh See Yong, Denise   g.seeyongdenise@digipen.edu
@date    05/11/2021
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
#include "Engine/Header/ECS/Component/ComponentManager.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/Scene/SceneManager.hpp"
#include "Engine/Header/Serialize/GameSceneSerializer.hpp"

namespace Engine {
	class ObjectCommand : public ICommand
	{
	public:
		//no commands for objects
	};

	//commands for adding state
	class ObjectAddState : public ObjectCommand
	{
	public:
		std::string scene_id;
		std::string newScene = std::string{};
		std::string oldScene = std::string{};
		Scene* currentScene = nullptr;

		void SetOldScene(std::string oldScene);
		void SetNewScene(std::string newScene);

		//undo the changes made to the objects
		void undo();
		//redo the changes made to the objects
		//void redo();

	private:
		std::stack <std::unique_ptr<ICommand>> commands;

	};

	////commands for deleting state
	//class ObjectDeleteState : public ObjectCommand
	//{
	//public:
	//	std::string scene_id;
	//	std::string newScene = std::string{};
	//	std::string oldScene = std::string{};

	//	void SetOldScene(std::string oldScene);
	//	void SetNewScene(std::string newScene);

	//	//undo the changes made to the objects
	//	void undo();
	//	//redo the changes made to the objects
	//	//void redo();

	//};
}
#endif
