/* Start Header**********************************************************************************/
/*
@file    ObjectCommand.hpp
@author  Goh See Yong, Denise   g.seeyongdenise@digipen.edu	100%
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

#include "Editor/Header/Commands/Command.hpp"
#include "Editor/Header/GUI/GUI_ClickCheck.hpp"

#include "Engine/Header/ECS/Component/ComponentManager.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/Scene/SceneManager.hpp"
#include "Engine/Header/Serialize/GameSceneSerializer.hpp"


#include "Engine/Header/Input/Input.hpp"
#include <iostream>

#include <vector>
#include <deque>
#include <stack>
#include <memory>

namespace Editor {

	namespace GUI_Windows {
	class ObjectCommand : public ICommand
	{
		//no commands for objects
	};

	//---------------------------------------------------------------------------------------------------------------
	//Using
	class ObjectTransformChangeCommand : public ObjectCommand
	{

	public:


		//undo the changes made to the objects
		void undo() override;

		//redo the changes made to the objects
		void redo() override;

		void record() override;

		void execute() override;

		ObjectTransformChangeCommand(Engine::TransformComponent _prevTransform, Engine::TransformComponent _nextTransform);
		ObjectTransformChangeCommand() = delete;

	private:
		Engine::TransformComponent prevTransform;
		Engine::TransformComponent nextTransform;

	};
	//---------------------------------------------------------------------------------------------------------------


	//commands for undo and redo adding game object transform component
	class ObjectAddCommand : public ObjectCommand
	{
		Engine::Entity_id object_ID = Engine::Entity_id{};
		Engine::Entity_id entity_id = Engine::Entity_id{};
		Engine::Entity_id selectable = Engine::Entity_id{};
		std::map<int, Engine::Entity_id> entity_selected = std::map<int, Engine::Entity_id>{};

	public:

		//undo the changes made to the objects
		void undo() override;

		//redo the changes made to the objects
		void redo() override;

		void record() override;

		void execute() override;

	};

	struct TransformContainer
	{

	};

	

	class ObjectTransformCommand : public ObjectCommand
	{
		Engine::Entity_id id{};

		std::map<int, Engine::Entity_id> entity_selected{};

		//current position
		Engine::DreamMath::vec2 _currentposition;

		//old position for transform component
		Engine::DreamMath::vec2 _oldposition;

		//new position for transform component
		Engine::DreamMath::vec2 _newposition;

		//checking if undo or redo
		bool check_redo;

	public:

		Engine::DreamMath::vec2 GetTransformPosition();

		//setting old position
		void SetOldPosition(Engine::DreamMath::vec2 _oldPosition);
		//void SetOldPosition(unsigned int* id = nullptr);
		
		// setting new position
		void SetNewPosition(Engine::DreamMath::vec2 _newPosition);
		//void SetNewPosition(unsigned int* id = nullptr);

		//currently stored transforms to each transform component
		//void StoredTransform(std::map<int, Engine::Entity_id>& entity_selected, Engine::DreamMath::vec2 positions);
		void StoredTransform(Engine::Entity_id entity_id, Engine::DreamMath::vec2 positions);
		
		//undo the changes made to the objects
		void undo() override;

		//redo the changes made to the objects
		void redo() override;

		void record() override;

		void execute() override;

	private:
		Engine::DreamMath::vec2 _position;
		Engine::DreamMath::vec2 _localposition;

	};

	//commands for undo and redo deleting game object
	class ObjectDeleteCommand : public ObjectCommand
	{
		Engine::Entity_id object_ID;

	public:

		//void AddObject(Engine::Entity_id object_ID);
		//undo the changes made to the objects
		void undo() override;

		//redo the changes made to the objects
		void redo() override;

		void execute() override;

	};

	//commands for undo and redo parenting game object
	class ObjectParentCommand : public ObjectCommand
	{
		Engine::Entity_id object_ID;
		std::map<int, Engine::Entity_id> entity_selected;

	public:

		//undo the changes made to the objects
		void undo() override;
		//redo the changes made to the objects
		//void redo();

		void execute() override;

	};

	//commands for undo for gizmo
	class ObjectGizmoCommand : public ObjectCommand
	{
	public:

		//undo the changes made to the objects
		void undo() override;
		//redo the changes made to the objects
		//void redo();

		void record() override;

		void execute() override;

	};

	//command for undo naming of entity
	class ObjectNameCommand : public ObjectCommand
	{
		Engine::Entity_id entity_selected = Engine::Entity_id{};

	public:

		//undo
		void undo() override;

		void record() override;

		void execute() override;
	};

	//commands for undo 

	//commands for adding state
	//class ObjectAddState : public ObjectCommand
	//{
	//public:
	//	std::string scene_id;
	//	std::string newScene = std::string{};
	//	std::string oldScene = std::string{};
	//	Scene* currentScene = nullptr;

	//	void SetOldScene(std::string oldScene);
	//	void SetNewScene(std::string newScene);

	//	//undo the changes made to the objects
	//	void undo();
	//	//redo the changes made to the objects
	//	//void redo();

	//private:
	//	std::stack <std::unique_ptr<ICommand>> commands;

	//};

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

}
#endif
