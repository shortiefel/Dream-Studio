/* Start Header**********************************************************************************/
/*
@file    Scripting.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    21/09/2021
\brief
#include "Engine/Header/Script/Scripting.hpp"
This file contain the declaration of Scripting


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SCRIPTING_HPP
#define SCRIPTING_HPP

#include "Engine/Header/Script/ScriptClass.hpp"
#include "Engine/Header/Script/MonoFunctionType.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"

namespace Engine {
	namespace Scripting {
		/*-----------------------------------------------------
		Invoke Mono functions in CSClass
		-----------------------------------------------------*/
		void Mono_Runtime_Invoke(const CSScriptInstance& _csScriptInstance, MonoFunctionType _type, void** _param = nullptr);
		/*-----------------------------------------------------
		Set up mono
		-----------------------------------------------------*/
		void Setup();
		/*-----------------------------------------------------
		Clean up mono
		-----------------------------------------------------*/
		void Cleanup();
		/*-----------------------------------------------------
		Destroy child domain
		-Check if child domain exist
		-delete if it exist
		-----------------------------------------------------*/
		void DestroyChildDomain();
		/*-----------------------------------------------------
		static void Stop();
		Compile CS files together
		-----------------------------------------------------*/
		bool CompileCSInternal(bool play);
		/*-----------------------------------------------------
		Called when play button is pressed
		-Stop child domain
		-Create child domain
		-Load assemblies
		-----------------------------------------------------*/
		void ReloadMono();
		/*-----------------------------------------------------
		Initialize the scripts in mono
		-Call mono Constructor
		-Call mono Init
		-----------------------------------------------------*/
		void InitScript(const Entity_id& entity_id, const CSScriptInstance& csScriptInstance);
		/*-----------------------------------------------------
		-To add/remove class from map
		-Find the function from c#
		-----------------------------------------------------*/
		bool InitCSClass(CSScriptInstance& _csScriptInstanc, const Entity_id& entity_ide);
		void InitAllCSClass();
		/*-----------------------------------------------------
		-To add/remove public variable from map
		-Set their values
		-----------------------------------------------------*/
		void InitVariable(CSScriptInstance& _csScriptInstance);
		void InitAllPublicVariable();

		/*-----------------------------------------------------
		-Open Visual Studio file
		-----------------------------------------------------*/
		void OpenVS(std::string fileName);
		/*-----------------------------------------------------
		-Set function ptr that will be overwritten in editor to display exception
		-----------------------------------------------------*/
		void SetDisplayFuncPtr(void(*fp)(std::string));
		/*-----------------------------------------------------
		-Set function ptr that will be overwritten in editor to display compile data
		-----------------------------------------------------*/
		void SetCompileFuncPtr(void(*fp)());
	}
}

#endif