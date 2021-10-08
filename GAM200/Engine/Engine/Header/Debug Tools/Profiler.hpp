/* Start Header**********************************************************************************/
/*
@file    Profiler.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    07/10/2021
\brief
This file contain the Profiler declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <vector>

#include "Engine/Header/Singleton/Singleton.hpp"
#include "Engine/Header/Time/Timer.hpp"

namespace Engine {
	struct ProfilerResult {
		const char* name;
		float time;
	};

	class Profiler : public Singleton<Profiler> {
	public:
		std::vector<ProfilerResult> profilerResult;

		void DisplayProfilerResult();

	private:
		SINGLETON_SETUP(Profiler);
	};
}

#define PROFILER_START(name) Engine::Timer timer##__LINE__(name, [&](Engine::ProfilerResult result) {\
Engine::Profiler::GetInstance().profilerResult.emplace_back(result); });

#endif