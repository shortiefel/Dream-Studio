/* Start Header**********************************************************************************/
/*
@file    FunctionOverride.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    31/10/2021
\brief
#include "Editor/Header/FunctionOverride.hpp"
This file contain the definition of FunctionOverride
This file override function pointer in Engine. Example printing text from Engine to Editor


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include <fstream>
#include <sstream>

#include "Editor/Header/FunctionOverride.hpp"

#include "Editor/Header/GUI/GUI_Windows/GUI_ConsoleWindow.hpp"
#include "Editor/Header/GUI/GUI_Windows/GUI_GameWindow.hpp"

#include "Engine/Header/Script/Scripting.hpp"
#include "Engine/Header/Script/ScriptInternalCall.hpp"



namespace Editor {
	void Override_Function() {
		Engine::SetGetViewportFunc(GUI_Windows::GetViewport);
		Engine::SetGetMousePositionFunc(GUI_Windows::GetMousePositionGameWindow);
		Engine::Scripting::SetDisplayFuncPtr([](std::string str) { GUI_Windows::GUI_Console_Add(GUI_Windows::ConsoleString{ str.c_str() }); });
		Engine::Scripting::SetCompileFuncPtr([]() {
			//Read compile result
			std::ifstream fs{ "Data/msbuild.log" };
			if (fs.is_open()) {
				std::ostringstream buffer;
				buffer << fs.rdbuf();

				GUI_Windows::GUI_Console_Add(GUI_Windows::ConsoleString{ buffer.str().c_str() });
			}

			fs.close();
			});
	}
}
