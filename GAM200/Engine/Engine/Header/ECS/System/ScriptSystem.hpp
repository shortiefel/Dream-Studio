/* Start Header**********************************************************************************/
/*
@file    ScriptSystem.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

#include "Engine/Header/Singleton/Singleton.hpp"

#include "Engine/Header/Script/ScriptClass.hpp"
#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {
	//map (entity id, map(classname, CSscript)
	using CSEntityClassInstance = std::unordered_map<unsigned int, CSClassInstance>;

	class ScriptSystem : public Singleton<ScriptSystem> {
	public:
		/*-----------------------------------------------------
		Start runtime
		-----------------------------------------------------*/
		void PlayInit();
		/*-----------------------------------------------------
		Update runtime
		-----------------------------------------------------*/
		void PlayRunTime();
		/*-----------------------------------------------------
		static void Stop();
		Compile CS files together
		-----------------------------------------------------*/
		bool CompileCS();
		/*-----------------------------------------------------
		Update information by
		-Reinstantiating Classes
		-Adding/Removing public variable from map
		Called when saving/playing
		-----------------------------------------------------*/
		void UpdateMapData();
		/*-----------------------------------------------------
		Create ScriptSystem
		-----------------------------------------------------*/
		void Create();
		/*-----------------------------------------------------
		Destroy ScriptSystem
		-----------------------------------------------------*/
		void Destroy();

	private:
		SINGLETON_SETUP(ScriptSystem);
	};
}

#endif