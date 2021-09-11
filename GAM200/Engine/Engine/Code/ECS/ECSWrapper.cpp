/* Start Header**********************************************************************************/
/*
@file    ECSWrapper.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    08/09/2021
\brief
This file is the wrapper file for ECS
-It is made such that in the future the ECS can be changed easily


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/ECSWrapper.hpp"
#include "Engine/Header/Script/ScriptEngine.hpp"


namespace Engine {
	Coordinator DreamECS::gCoordinator;

	void DreamECS::Init()
	{
		gCoordinator.Init();
	}

	Entity DreamECS::CreateEntity()
	{
		return gCoordinator.createEntity();
	}

	void DreamECS::DuplicateEntity(Entity entFrom) {
		Entity entTo = gCoordinator.createEntity();
		gCoordinator.DuplicateEntity(entFrom, entTo);
		
		const auto& listOfClassInstance = ScriptEngine::csEntityClassInstance.find(entFrom)->second;
		CSClassInstance newClassInstance;
		for (auto& [className, scriptInstance] : listOfClassInstance) {
			newClassInstance.emplace(className, CSScriptInstance{ className });
		}

		ScriptEngine::csEntityClassInstance.emplace(entTo, std::move(newClassInstance));
	}

	void DreamECS::DestroyEntity(Entity entity)
	{
		gCoordinator.destroyEntity(entity);
	}

	void DreamECS::DestroyAllEntity()
	{
		gCoordinator.destroyAllEntity();
	}

	const std::vector<Entity>& DreamECS::GetUsedEntityVector() {
		return gCoordinator.GetUsedEntityVector();
	}

}