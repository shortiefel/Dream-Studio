

#pragma once

#include <Imgui/imgui.h>
#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/Commands/Command.hpp"
#include "Engine/Header/Commands/ObjectCommand.hpp"

#include <map>

namespace Editor {
	namespace GUI_Windows {
		class ICommand;
		class ObjectAddState;

		void GUI_Hierarchy(bool* hierarchy_bool, std::map<int, Engine::Entity_id>& entity_selected, ImGuiWindowFlags window_flags);
	}
}