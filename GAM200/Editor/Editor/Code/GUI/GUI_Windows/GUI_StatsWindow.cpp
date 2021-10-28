
#include "Editor/Header/GUI/GUI_Windows/GUI_StatsWindow.hpp"
#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/Time/DeltaTime.hpp"
#include "Engine/Header/Graphic/mesh.hpp"

#include <sstream>
namespace Editor {
	namespace GUI_Windows {
		void GUI_Stats(bool* stats_bool) {
			if (*stats_bool) {
				ImGui::Begin("Engine Stats", stats_bool);
				std::stringstream outputSS;
				outputSS << "FPS: ";
				outputSS.precision(2);
				outputSS << std::fixed << Engine::DeltaTime::GetInstance().GetFPS();

				ImGui::Text(outputSS.str().c_str());
				outputSS.str(std::string());

				outputSS << "Entity Count: ";
				outputSS << Engine::DreamECS::GetInstance().GetComponentArraySize<Engine::TransformComponent>();
				ImGui::Text(outputSS.str().c_str());
				outputSS.str(std::string());

				outputSS << "Number of Quads : ";
				outputSS << Engine::GraphicImplementation::Renderer::GetQuadStats().quadCount;
				ImGui::Text(outputSS.str().c_str());
				outputSS.str(std::string());


				outputSS << "Draw Count : ";
				outputSS << Engine::GraphicImplementation::Renderer::GetQuadStats().drawCount;
				ImGui::Text(outputSS.str().c_str());
				outputSS.str(std::string());

				ImGui::End();
			}
		}
	}
}
