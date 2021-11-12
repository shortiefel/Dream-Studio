/* Start Header**********************************************************************************/
/*
@file    Profiler.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
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
		double time;
	};

	class Profiler : public Singleton<Profiler> {
	public:
		std::vector<ProfilerResult> profilerResult;

		void DisplayProfilerResult();
		
		const float GetApplicationTime() const;
		const float GetRenderingTime() const;
		const float GetPhysicsTime() const;
		const float GetCollisionTime() const;
		const float GetScriptingTime() const;
		const float GetEventTime() const;
		const float GetMiscellaneousTime() const;

	private:
		double applicationTime = double{};
		double renderingTime = double{};
		double physicsTime = double{};
		double collisionTime = double{};
		double scriptingTime = double{};
		double eventTime = double{};
		double miscellaneousTime = double{};
		double totalTime = double{};

		SINGLETON_SETUP(Profiler);
	};
}

#define PROFILER_START(name) Engine::Timer timer(name, std::move([&](Engine::ProfilerResult&& result) {\
Engine::Profiler::GetInstance().profilerResult.emplace_back(std::move(result)); }));
//#define PROFILER_START(name) Engine::Timer timer(name, std::move([&](Engine::ProfilerResult&& result) {\
// }));

#endif