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

#include <Imgui/imgui.h>

//number of points in the graph (more = smoother)
#define PROFILER_COUNT 100

#define PLOT_LINE_PARAMETER 0, 0, 0, 100, ImVec2{ 0, 50 }

#define SET_ARRAY_VALUE(index)\
		renderingLines[index] = Engine::Profiler::GetInstance().GetRenderingTime();\
		physicsLines[index] = Engine::Profiler::GetInstance().GetPhysicsTime();\
		collisionLines[index] = Engine::Profiler::GetInstance().GetCollisionTime();\
		scriptingLines[index] = Engine::Profiler::GetInstance().GetScriptingTime();\
		eventLines[index] = Engine::Profiler::GetInstance().GetEventTime();\
		miscellaneousLines[index] = Engine::Profiler::GetInstance().GetMiscellaneousTime()

#define PLOT_LINES\
	ImGui::PlotLines("Rendering", renderingLines, lineIndex, PLOT_LINE_PARAMETER);\
	ImGui::PlotLines("Physics", physicsLines, lineIndex, PLOT_LINE_PARAMETER);\
	ImGui::PlotLines("Collision", collisionLines, lineIndex, PLOT_LINE_PARAMETER);\
	ImGui::PlotLines("Scripting", scriptingLines, lineIndex, PLOT_LINE_PARAMETER);\
	ImGui::PlotLines("Event", eventLines, lineIndex, PLOT_LINE_PARAMETER);\
	ImGui::PlotLines("Miscellaneous", miscellaneousLines, lineIndex, PLOT_LINE_PARAMETER);

namespace Editor {
	namespace GUI_Window {
		void GUI_Profiler(bool* profiler_bool) {
			if (*profiler_bool) {
				ImGui::Begin("Profiler", profiler_bool);
				//-1 due to the nature of the algorithm
				//if current loop is lineIndex = PROFILER_COUNT - 1
				//then previous loop should have set that index hence needing to lineIndex++ before set
				static int lineIndex = -1;
				static float renderingLines[PROFILER_COUNT]{};
				static float physicsLines[PROFILER_COUNT]{};
				static float collisionLines[PROFILER_COUNT]{};
				static float scriptingLines[PROFILER_COUNT]{};
				static float eventLines[PROFILER_COUNT]{};
				static float miscellaneousLines[PROFILER_COUNT]{};

				if (lineIndex >= PROFILER_COUNT - 1) {
					for (int i = 0; i < PROFILER_COUNT - 1; i++) {
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

				PLOT_LINES;
				ImGui::End();
			}
		}
	}
}