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
		double renderingTime = 0.f;
		double physicsTime = 0.f;
		double collisionTime = 0.f;
		double scriptingTime = 0.f;
		double eventTime = 0.f;
		double totalTime = 0.f;

		for (auto& result : profilerResult) {
			char label[50];
			strcpy_s(label, result.name);
			//strcat_s(label, " %0.3fms");
			//ImGui::Text(label, result.time);
			//printf("%s %0.3fms\n", label, result.time);
			
			if (result.name == "Rendering")
				renderingTime += result.time;
			else if (result.name == "Physics")
				physicsTime += result.time;
			else if (result.name == "Collision")
				collisionTime += result.time;
			else if (result.name == "Scripting")
				scriptingTime += result.time;
			else if (result.name == "Event")
				eventTime += result.time;
			else if (result.name == "Total")
				totalTime += result.time;

			//std::cout << "dfs " << label << result.time << "\n";
			//std::cout << result.name << ": " << result.time << std::endl;
		}

		std::cout << "Total Time: " << totalTime << std::endl;
		std::cout << "Rendering: " << renderingTime << std::endl;
		std::cout << "Physics: " << physicsTime << std::endl;
		std::cout << "Collision: " << collisionTime << std::endl;
		std::cout << "Scripting: " << scriptingTime << std::endl;
		std::cout << "Event: " << eventTime << std::endl;
		std::cout << "Miscellaneous: " << (totalTime - renderingTime - physicsTime - collisionTime - scriptingTime - eventTime) << std::endl;

		profilerResult.clear();
	}
}