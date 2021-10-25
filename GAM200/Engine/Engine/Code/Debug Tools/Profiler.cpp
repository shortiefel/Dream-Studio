/* Start Header**********************************************************************************/
/*
@file    Profiler.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    07/10/2021
\brief
This file contain the Profiler definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Profiler.hpp"
#include <iostream>

namespace Engine {
	void Profiler::DisplayProfilerResult() {
		applicationTime = 0.f;
		renderingTime = 0.f;
		physicsTime = 0.f;
		collisionTime = 0.f;
		scriptingTime = 0.f;
		eventTime = 0.f;
		totalTime = 0.f;

		for (auto& result : profilerResult) {
			char label[50];
			strcpy_s(label, result.name);
			//strcat_s(label, " %0.3fms");
			//ImGui::Text(label, result.time);
			//printf("%s %0.3fms\n", label, result.time);
			if (strcmp(result.name, "Application"))
				applicationTime += result.time;
			else if (strcmp(result.name, "Rendering"))
				renderingTime += result.time;
			else if (strcmp(result.name, "Physics"))
				physicsTime += result.time;
			else if (strcmp(result.name, "Collision"))
				collisionTime += result.time;
			else if (strcmp(result.name, "Scripting"))
				scriptingTime += result.time;
			else if (strcmp(result.name, "Event"))
				eventTime += result.time;
			else if (strcmp(result.name, "Total"))
				totalTime += result.time;
		}

		miscellaneousTime = totalTime - applicationTime - renderingTime - physicsTime - collisionTime - scriptingTime - eventTime;
		//std::cout << "Total Time: " << totalTime << std::endl;
		//std::cout << "Application : " << applicationTime << "\n";
		//std::cout << "Rendering: " << renderingTime << std::endl;
		//std::cout << "Physics: " << physicsTime << std::endl;
		//std::cout << "Collision: " << collisionTime << std::endl;
		//std::cout << "Scripting: " << scriptingTime << std::endl;
		//std::cout << "Event: " << eventTime << std::endl;
		//std::cout << "Miscellaneous: " << miscellaneousTime << std::endl;

		profilerResult.clear();
	}

	const float Profiler::GetApplicationTime() const {
		return 100.f * static_cast<float>(applicationTime / totalTime);
	}

	const float Profiler::GetRenderingTime() const {
		return 100.f * static_cast<float>(renderingTime/totalTime);
	}

	const float Profiler::GetPhysicsTime() const {
		return 100.f * static_cast<float>(physicsTime / totalTime);
	}

	const float Profiler::GetCollisionTime() const {
		return 100.f * static_cast<float>(collisionTime / totalTime);
	}

	const float Profiler::GetScriptingTime() const {
		return 100.f * static_cast<float>(scriptingTime / totalTime);
	}

	const float Profiler::GetEventTime() const {
		return 100.f * static_cast<float>(eventTime / totalTime);
	}

	const float Profiler::GetMiscellaneousTime() const {
		return 100.f * static_cast<float>(miscellaneousTime / totalTime);
	}
}