/* Start Header**********************************************************************************/
/*
@file    EngineCore.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
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

#include "Engine/Header/Singleton/Singleton.hpp"

namespace Engine {
	class EngineCore : public Singleton<EngineCore> {
	public:
		void Create();
		void Update(float dt);
		void Destroy();
	private:
		EngineCore() {}
		~EngineCore() {}

		friend class Singleton<EngineCore>;
	};
}

#endif