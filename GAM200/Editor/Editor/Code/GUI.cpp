#include "GUI.hpp"
#include "Layer/GUILayer.hpp"
#include "Engine/Header/Window.hpp"
#include "Engine/Header/Layer/LayerStack.hpp"

namespace Editor {
	void GUI::Create() {
		GUILayer::Create(Engine::Window::GetGLFWwindow(), Engine::Window::GetGLSLVersion());
		Engine::LayerStack::AddOverlayLayer(GUILayer::Get());
	}

	void GUI::Update() {

	}

	void GUI::Destroy() {
		GUILayer::Destroy();
	}
}