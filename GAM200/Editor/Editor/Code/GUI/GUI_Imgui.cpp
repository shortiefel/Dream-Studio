/* Start Header**********************************************************************************/
/*
@file    GUI_Imgui.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    16/10/2021
@brief
This file has the GUI_Imgui definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Editor/Header/GUI/GUI_Imgui.hpp"

#include <Imgui/imgui.h>
//#include <Imgui/imgui_internal.h>

namespace DreamImGui {
	void CheckBox_Dream(const char* _text, bool* _boolean) {
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
		ImGui::Checkbox(_text, _boolean);
		ImGui::PopStyleVar();
	}
	
}