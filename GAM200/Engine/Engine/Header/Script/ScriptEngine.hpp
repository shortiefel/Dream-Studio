/* Start Header**********************************************************************************/
/*
@file    ScriptEngine.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/08/2021
\brief
This file contain the declaration of ScriptEngine


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPT_ENGINE_HPP
#define SCRIPT_ENGINE_HPP

//#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/Script/ScriptClass.hpp"

namespace Engine {
	namespace Scripting {

		//map (entity id, map(classname, CSscript)
		using CSEntityClassInstance = std::unordered_map<unsigned int, CSClassInstance>;

		
		class ScriptEngine {
		public:
			static void InitEntityClassInstance();
			static void Play();
			/*-----------------------------------------------------
			Set up mono
			-----------------------------------------------------*/
			static void Create();
			/*-----------------------------------------------------
				Clean up mono
			-----------------------------------------------------*/
			static void Destroy();
			/*-----------------------------------------------------
				Called when play button is pressed (After ReloadMono)
				-Load objects
				-Deserialize
				-Call Constructor
				-Call init object
			-----------------------------------------------------*/
			static void ReloadObject(MonoObject*& object, CSClass& csScript, void** param);
			/*-----------------------------------------------------
				Call a specific virtual function
				E.g: Init, Update
			-----------------------------------------------------*/
			static void CallFunction(MonoObject*& object, MonoMethod*& method, void** param = nullptr);


		//private:
			static CSEntityClassInstance csEntityClassInstance;
		};
	}
}

#endif