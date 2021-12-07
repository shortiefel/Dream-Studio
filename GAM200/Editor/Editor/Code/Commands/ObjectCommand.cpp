/* Start Header**********************************************************************************/
/*
@file    ObjectCommand.cpp
@author  Goh See Yong, Denise   g.seeyongdenise@digipen.edu	100%
@date    05/11/2021
\brief
This file contain the undo / redo commands for game object/ scene


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/Commands/ObjectCommand.hpp"

#include "Engine/Header/Window.hpp"
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/Graphic/Picking2D.hpp"
#include "Engine/Header/Parent/ParentManager.hpp"
#include "Engine/Header/Input/Input.hpp"

#include <Imgui/imgui.h>

namespace Editor
{
	namespace GUI_Windows {
		//---------------------------------------------------------------------------------------------------------------
		//Using
		void ObjectTransformChangeCommand::undo()
		{
			Engine::TransformComponent* tc = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(prevTransform.GetEntityId());
			if (tc != nullptr) *tc = prevTransform;
			std::cout << "Gizmo Undo " << prevTransform.position << " " << prevTransform.GetEntityId() << "\n";
		}

		void ObjectTransformChangeCommand::redo()
		{
			Engine::TransformComponent* tc = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(nextTransform.GetEntityId());
			if (tc != nullptr) *tc = nextTransform;
			std::cout << "Gizmo Redo " << nextTransform.position << " " << nextTransform.GetEntityId() << "\n";
		}

		void ObjectTransformChangeCommand::record()
		{

		}

		void ObjectTransformChangeCommand::execute()
		{

		}

		ObjectTransformChangeCommand::ObjectTransformChangeCommand(Engine::TransformComponent _prevTransform, Engine::TransformComponent _nextTransform) :
			prevTransform{ _prevTransform }, nextTransform{ _nextTransform } {
			std::cout << prevTransform.GetEntityId() << " " << _nextTransform.GetEntityId() << "\n";
		}
		//---------------------------------------------------------------------------------------------------------------

		void ObjectTransformCommand::undo()
		{
			Engine::TransformComponent* transformComp = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(oldposition.GetEntityId());
			if (transformComp != nullptr)
			{
				*transformComp = oldposition;
			}
			std::cout << "Inspector undo " << oldposition.position << " " << oldposition.GetEntityId() << "\n"; 

		}

		void ObjectTransformCommand::redo()
		{
			Engine::TransformComponent* tc = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(newposition.GetEntityId());
			if (tc != nullptr) *tc = newposition;
			std::cout << "Inspector Redo " << newposition.position << " " << newposition.GetEntityId() << "\n";
		}

		void ObjectTransformCommand::record()
		{

		}

		void ObjectTransformCommand::execute()
		{

		}

		ObjectTransformCommand::ObjectTransformCommand(Engine::TransformComponent _oldposition, Engine::TransformComponent _newposition) :
			oldposition{ _oldposition }, newposition{ _newposition }
		{
			std::cout << oldposition.GetEntityId() << " " << newposition.GetEntityId() << "\n";
		}

		void ObjectAddCommand::undo()
		{
			//undo adding game object
		}

		void ObjectAddCommand::redo()
		{
			Engine::TransformComponent* transform = Engine::dreamECSGame->GetComponentPTR<Engine::TransformComponent>(GetTarget(entity_selected));
			if (transform != nullptr)
			{
				Engine::dreamECSGame->AddComponent<Engine::TransformComponent>(GetTarget(entity_selected));

			}
		}


		void ObjectAddCommand::execute()
		{

		}

		void ObjectAddCommand::record()
		{

		}

		void ObjectParentCommand::undo()
		{
			for (const auto& [index, entity_id] : entity_selected) {
				Engine::dreamECSGame->Unparent(entity_id);
			}
		}

		void ObjectParentCommand::execute()
		{

		}


		void ObjectNameCommand::undo()
		{
			//auto& entity_map = Engine::dreamECSGame->GetUsedEntityMap();
			//const auto& itr = entity_map.find(entity_selected);
			//std::string& entity_name = itr->second.name;
			//char* old_name = oldName.c_str();
			//strcpy(old_name, entity_name.c_str());
			std::cout << "Name undo " << oldName << "\n";

		}

		void ObjectNameCommand::redo()
		{

			std::cout << "Name Redo " << newName << "\n";
		}

		void ObjectNameCommand::record()
		{

		}

		void ObjectNameCommand::execute()
		{

		}

		ObjectNameCommand::ObjectNameCommand(std::string _oldName, std::string _newName) :
			oldName{ _oldName }, newName{ _newName }
		{
			std::cout << oldName << " " << newName << "\n";
		}
	}
}