/* Start Header**********************************************************************************/
/*
@file    ScriptSystem.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    19/06/2021
\brief
This file has the class to manage scripts: ScriptSystem
includes declaration to static function for a singleton ScriptSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPT_SYSTEM_HPP
#define SCRIPT_SYSTEM_HPP

#include "Engine/Header/pch.hpp"
#include "Engine/Header/ECS/System/System.hpp"

namespace Engine {
	class ScriptSystem : public System {
	public:
		static bool Create(const std::shared_ptr<ScriptSystem>& scriptSystem);
		virtual void Destroy() override;
		~ScriptSystem();

		//Called when user press play
		static void Play();
		//Opposite of play
		static void Stop();
		static void Update(float dt);

	private:
		static std::shared_ptr<ScriptSystem> SS;
	};
}

#endif