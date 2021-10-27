

#pragma once

#include <Imgui/imgui.h>
#include "Engine/Header/ECS/DreamECS.hpp"

namespace Editor {
	namespace GUI_Windows {
		void GUI_Inspector(bool* inspector_bool, float textSize, Engine::Entity_id& entity_selected, ImGuiWindowFlags window_flags);
	}
}