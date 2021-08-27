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
			static void Play();

		//private:
			static CSEntityClassInstance csEntityClassInstance;
		};
	}
}

#endif