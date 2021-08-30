/* Start Header**********************************************************************************/
/*
@file    EngineCore.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    24/07/2021
\brief
This file has the function declaration for class EngineCore


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef ENGINE_CORE_HPP
#define ENGINE_CORE_HPP
#include "Engine/Header/Event/UtilityEvent.hpp"
namespace Engine {
	class EngineCore {
	public:
		static void Create();
		static void Update(float dt, bool defaultRender);
		static void Destroy();
	private:
	};
}

#endif