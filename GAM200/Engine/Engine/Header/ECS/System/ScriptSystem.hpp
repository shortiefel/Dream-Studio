/* Start Header**********************************************************************************/
/*
@file    ScriptSystem.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    26/08/2021
\brief
This file contain the declaration of ScriptSystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPT_SYSTEM_HPP
#define SCRIPT_SYSTEM_HPP

//#include "Engine/Header/ECS/ECSGlobal.hpp"
#include "Engine/Header/Script/ScriptClass.hpp"
#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {
	//map (entity id, map(classname, CSscript)
	using CSEntityClassInstance = std::unordered_map<unsigned int, CSClassInstance>;


	class ScriptSystem {
	public:

		/*-----------------------------------------------------
		Start runtime
		-----------------------------------------------------*/
		static void PlayInit();
		/*-----------------------------------------------------
		Update runtime
		-----------------------------------------------------*/
		static void PlayRunTime();
		/*-----------------------------------------------------
		Pausing the runtime
		-opposite of play
		-----------------------------------------------------*/
		static void Stop();
		//Compile CS files together
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

		/*-----------------------------------------------------
			Call a specific virtual function
			E.g: Init, Update
		-----------------------------------------------------*/
		static void CallFunction(MonoObject*& object, MonoMethod*& method, void** param = nullptr);
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

		//static CSEntityClassInstance csEntityClassInstance;


		static void SerializeClass(const SSerializer& _serializer, const CSClassInstance& _classInstance);
		static void SerializeVariable(const SSerializer& _serializer, const CSScriptInstance& _scriptInstance);
		static void Deserialize(const DSerializer& _serializer, CSClassInstance& classInstance);
	};
}

#endif