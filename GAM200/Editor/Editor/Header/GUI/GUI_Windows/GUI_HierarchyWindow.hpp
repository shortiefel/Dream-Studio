

#pragma once

#include <Imgui/imgui.h>
#include "Engine/Header/ECS/DreamECS.hpp"

namespace Editor {
	namespace GUI_Windows {
		void GUI_Hierarchy(bool* hierarchy_bool, Engine::Entity_id& entity_selected, ImGuiWindowFlags window_flags);
	}
}