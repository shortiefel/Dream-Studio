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

#include "Engine/Header/ECS/Coordinator.hpp"

namespace Engine {
	extern Coordinator gCoordinator;
	std::shared_ptr<ScriptSystem> ScriptSystem::SS;


	void ScriptSystem::Update(float dt) {
		for (auto const& entity : SS->mEntities) {
			auto& cscript = gCoordinator.GetCom<Custom_Script>(entity);
			cscript->Update(entity, dt);
		}
	}

	//Function is called when GameScene Play function is called
	//Function is called whenever user press play
	void ScriptSystem::Play() {
		for (auto const& entity : SS->mEntities) {
			auto& cscript = gCoordinator.GetCom<Custom_Script>(entity);
			cscript->Init(entity);
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