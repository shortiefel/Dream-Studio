/* Start Header**********************************************************************************/
/*
@file    GUI_ProfilerWindow.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    18/08/2021
\brief
This file contain the ProfilerWindow definition
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/GUI/GUI_Windows/GUI_ProfilerWindow.hpp"

#include "Engine/Header/pch.hpp"
#include "Engine/Header/Window.hpp"
#include "Engine/Header/Debug Tools/Profiler.hpp"
#include "Engine/Header/Time/DeltaTime.hpp"
#include "Engine/Header/Management/GameState.hpp"

#include <sstream>      // std::stringstream
#include <iostream>     // std::fixed
#include <iomanip>      // std::setprecision

#include <Imgui/imgui.h>

#define COUNTDOWN_TIMER 0.01f
#define WAIT_TIME 5.f

//number of points in the graph (more = smoother)
#define PROFILER_COUNT 20

#define PLOT_LINE_PARAMETER 0, 0, 0, 100, ImVec2{ 0, 50 }

#define SET_ARRAY_VALUE(index)\
		fpsLines[index] = fps;\
		applicationLines[index] = Engine::Profiler::GetInstance().GetApplicationTime();\
		renderingLines[index] = Engine::Profiler::GetInstance().GetRenderingTime();\
		physicsLines[index] = Engine::Profiler::GetInstance().GetPhysicsTime();\
		collisionLines[index] = Engine::Profiler::GetInstance().GetCollisionTime();\
		scriptingLines[index] = Engine::Profiler::GetInstance().GetScriptingTime();\
		eventLines[index] = Engine::Profiler::GetInstance().GetEventTime();\
		miscellaneousLines[index] = Engine::Profiler::GetInstance().GetMiscellaneousTime()

#define PLOT_LINES\
	ImGui::PlotLines(fpsSS.str().c_str(), fpsLines, lineIndex, 0, 0, minfps, maxfps, ImVec2{ 0, 50 });\
	ImGui::PlotLines(appSS.str().c_str(), applicationLines, lineIndex, PLOT_LINE_PARAMETER);\
	ImGui::PlotLines(renderSS.str().c_str(), renderingLines, lineIndex, PLOT_LINE_PARAMETER);\
	ImGui::PlotLines(physicSS.str().c_str(), physicsLines, lineIndex, PLOT_LINE_PARAMETER);\
	ImGui::PlotLines(collisionSS.str().c_str(), collisionLines, lineIndex, PLOT_LINE_PARAMETER);\
	ImGui::PlotLines(scriptSS.str().c_str(), scriptingLines, lineIndex, PLOT_LINE_PARAMETER);\
	ImGui::PlotLines(eventSS.str().c_str(), eventLines, lineIndex, PLOT_LINE_PARAMETER);\
	ImGui::PlotLines(miscSS.str().c_str(), miscellaneousLines, lineIndex, PLOT_LINE_PARAMETER);

namespace Editor {
	namespace GUI_Windows {
		void GUI_Profiler(bool* profiler_bool) {
			Engine::Profiler::GetInstance().DisplayProfilerResult();

			static float updateTimer = 0.f;
			updateTimer -= COUNTDOWN_TIMER;
			if (*profiler_bool) {
				ImGui::Begin("Profiler", profiler_bool);
				//-1 due to the nature of the algorithm
				//if current loop is lineIndex = PROFILER_COUNT - 1
				//then previous loop should have set that index hence needing to lineIndex++ before set
				static int lineIndex = -1;
				static float fpsLines[PROFILER_COUNT]{};
				static float applicationLines[PROFILER_COUNT]{};
				static float renderingLines[PROFILER_COUNT]{};
				static float physicsLines[PROFILER_COUNT]{};
				static float collisionLines[PROFILER_COUNT]{};
				static float scriptingLines[PROFILER_COUNT]{};
				static float eventLines[PROFILER_COUNT]{};
				static float miscellaneousLines[PROFILER_COUNT]{};

				static float fps = float{};
				static float maxfps = std::numeric_limits<float>::min();
				static float minfps = std::numeric_limits<float>::max();

				if (updateTimer <= 0.f) {


					fps = Engine::DeltaTime::GetInstance().GetFPS();
					maxfps = fps > maxfps ? fps : maxfps;
					minfps = fps < minfps ? fps : minfps;

					updateTimer = WAIT_TIME;

					if (lineIndex >= PROFILER_COUNT - 1) {
						for (int i = 0; i < PROFILER_COUNT - 1; i++) {
							fpsLines[i] = fpsLines[i + 1];
							applicationLines[i] = applicationLines[i + 1];
							renderingLines[i] = renderingLines[i + 1];
							physicsLines[i] = physicsLines[i + 1];
							collisionLines[i] = collisionLines[i + 1];
							scriptingLines[i] = scriptingLines[i + 1];
							eventLines[i] = eventLines[i + 1];
							miscellaneousLines[i] = miscellaneousLines[i + 1];
						}
						SET_ARRAY_VALUE(PROFILER_COUNT - 1);
					}

					else {
						lineIndex++;
						SET_ARRAY_VALUE(lineIndex);
					}
				}

				std::stringstream fpsSS; fpsSS << "FPS: " << std::fixed << std::setprecision(2) << fpsLines[lineIndex];
				std::stringstream appSS; appSS << "Application: " << std::fixed << std::setprecision(2) << applicationLines[lineIndex] << "%";
				std::stringstream renderSS; renderSS << "Rendering: " << std::fixed << std::setprecision(2) << renderingLines[lineIndex] << "%";
				std::stringstream physicSS; physicSS << "Physics: " << std::fixed << std::setprecision(2) << physicsLines[lineIndex] << "%";
				std::stringstream collisionSS; collisionSS << "Collision: " << std::fixed << std::setprecision(2) << collisionLines[lineIndex] << "%";
				std::stringstream scriptSS; scriptSS << "Scripting: " << std::fixed << std::setprecision(2) << scriptingLines[lineIndex] << "%";
				std::stringstream eventSS; eventSS << "Event: " << std::fixed << std::setprecision(2) << eventLines[lineIndex] << "%";
				std::stringstream miscSS; miscSS << "Miscellaneous: " << std::fixed << std::setprecision(2) << miscellaneousLines[lineIndex] << "%";

				PLOT_LINES;
				ImGui::End();
			}
		}
	}
}