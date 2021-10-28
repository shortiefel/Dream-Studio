

#pragma once

#include <Imgui/imgui.h>
#include "Engine/Header/ECS/DreamECS.hpp"

#include <map>

namespace Editor {
	namespace GUI_Windows {
		void GUI_Hierarchy(bool* hierarchy_bool, std::map<int, Engine::Entity_id>& entity_selected, ImGuiWindowFlags window_flags);
	}
}