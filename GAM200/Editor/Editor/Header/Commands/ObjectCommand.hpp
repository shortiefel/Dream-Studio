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
	//command for gizmo
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

	//command for inspector transform
	class ObjectTransformCommand : public ObjectCommand
	{

	public:
		
		//undo the changes made to the objects
		void undo() override;

		//redo the changes made to the objects
		void redo() override;

		void record() override;

		void execute() override;


		ObjectTransformCommand(Engine::TransformComponent _oldposition, Engine::TransformComponent _newposition);
		ObjectTransformCommand() = delete;

	private:
		Engine::TransformComponent oldposition;
		Engine::TransformComponent newposition;

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
		void redo();

		void execute() override;

	};

	//command for undo naming of entity
	class ObjectNameCommand : public ObjectCommand
	{
		Engine::Entity_id entity_selected;

	public:

		//undo
		void undo() override;

		//redo
		void redo() override;

		void record() override;

		void execute() override;

		ObjectNameCommand(std::string _oldName, std::string _newName);
		ObjectNameCommand() = delete;

	private:
		std::string newName;
		std::string oldName;

	};

	}

}
#endif
