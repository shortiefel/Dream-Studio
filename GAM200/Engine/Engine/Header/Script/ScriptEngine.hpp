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
			
			static void PlayInit();
			static void PlayRunTime();

			static bool CompileCS();


			
			/*-----------------------------------------------------
			Update information by
			-Reinstantiating Classes
			-Adding/Removing public variable from map
			Called when saving/playing
			-----------------------------------------------------*/
			static void UpdateMapData();
			/*-----------------------------------------------------
			Get enum CSType from MonoType
			-----------------------------------------------------*/
			static CSType GetCSType(MonoType* mt);
			/*-----------------------------------------------------
			Set up mono
			-----------------------------------------------------*/
			static void Create();
			/*-----------------------------------------------------
				Clean up mono
			-----------------------------------------------------*/
			static void Destroy();
			/*-----------------------------------------------------
			Called when play button is pressed
			-Stop child domain
			-Create child domain
			-Load assemblies
			-----------------------------------------------------*/
			static void ReloadMono();
			
			///*-----------------------------------------------------
			//	Called when play button is pressed (After ReloadMono)
			//	-Load objects
			//	-Deserialize
			//	-Call Constructor
			//	-Call init object
			//-----------------------------------------------------*/
			//static void ReloadObject(MonoObject*& object, CSClass& csScript, void** param);
			/*-----------------------------------------------------
				Call a specific virtual function
				E.g: Init, Update
			-----------------------------------------------------*/
			static void CallFunction(MonoObject*& object, MonoMethod*& method, void** param = nullptr);


			static CSEntityClassInstance csEntityClassInstance;

		//private:
			/*-----------------------------------------------------
			-To add/remove public variable from map
			-Set their values
			-----------------------------------------------------*/
			static void InitPublicVariable();
			/*-----------------------------------------------------
			-To add/remove class from map
			-Find the function from c#
			-----------------------------------------------------*/
			static void InitEntityClassInstance();
		};
	}
}

#endif