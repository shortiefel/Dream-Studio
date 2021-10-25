/* Start Header**********************************************************************************/
/*
@file    Scripting.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    21/09/2021
\brief
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
		bool CompileCSInternal();
		/*-----------------------------------------------------
		Called when play button is pressed
		-Stop child domain
		-Create child domain
		-Load assemblies
		-----------------------------------------------------*/
		void ReloadMono();
		/*-----------------------------------------------------
		-To add/remove class from map
		-Find the function from c#
		-----------------------------------------------------*/
		bool InitCSClass(CSScriptInstance& _csScriptInstance); //Return whether class exist
		void InitAllCSClass();
		/*-----------------------------------------------------
		-To add/remove public variable from map
		-Set their values
		-----------------------------------------------------*/
		void InitVariable(CSScriptInstance& _csScriptInstance);
		void InitAllPublicVariable();
	}
}

#endif