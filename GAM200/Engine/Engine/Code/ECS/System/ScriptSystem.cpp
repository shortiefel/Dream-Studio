/* Start Header**********************************************************************************/
/*
@file    ScriptSystem.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file has the function definition for class ScriptSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/System/ScriptSystem.hpp"
#include "Engine/Header/ECS/Component/Script/ScriptComponent.hpp"
#include "Engine/Header/Script/ScriptEmbed.hpp"

#include "Engine/Header/ECS/Coordinator.hpp"

#include <mono/metadata/threads.h>


namespace Engine {
	extern Coordinator gCoordinator;
	std::shared_ptr<ScriptSystem> ScriptSystem::SS;

	//static std::vector <std::pair<Entity, MonoObject*>> instances_v;

	static std::unordered_map<Entity, std::shared_ptr<MonoObject*>> entityToMonoObject;
	
	void ScriptSystem::Update(float dt) {
		std::string func = "Update";
		for (auto const& entity : SS->mEntities) {
			auto& cscript = gCoordinator.GetCom<CSharpScript>(entity);

			ScriptEmbed::CallFunction(entityToMonoObject[entity], cscript.className, func);
		}
	}

	//Function is called when GameScene Play function is called
	//Function is called whenever user press play
	void ScriptSystem::Play() {
		entityToMonoObject.clear();

		ScriptEmbed::ReloadMono();

		std::shared_ptr<MonoObject*> obj = nullptr;
		for (auto const& entity : SS->mEntities) {
			auto& cscript = gCoordinator.GetCom<CSharpScript>(entity);
			//Store obj---------------------------------------------------------
			ScriptEmbed::ReloadObject(obj, cscript.className);

			entityToMonoObject[entity] = obj;
		}
	}

	//Function is opposite of play
	void ScriptSystem::Stop() {
		/*for (auto const& entity : SS->mEntities) {
			auto& cscript = gCoordinator.GetCom<Custom_Script>(entity);
			cscript->OnDestroy();
		}*/
	}

	bool ScriptSystem::Create(const std::shared_ptr<ScriptSystem>& scriptSystem) {
		SS = scriptSystem;
		LOG_INSTANCE("Script System created");

		return true;
	}
	void ScriptSystem::Destroy() {
		LOG_INSTANCE("Script System destroyed");
		//delete s_instance; 
	}

	ScriptSystem::~ScriptSystem() { Destroy(); }

}