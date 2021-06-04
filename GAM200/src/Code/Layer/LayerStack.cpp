#include "../../Header/Debug Tools/Logging.hpp"
#include "../../Header/Layer/LayerStack.hpp"

LayerStack* LayerStack::m_instance = 0;
std::vector<Layer*> LayerStack::layerStack;
unsigned int LayerStack::layerCount = 0;

void LayerStack::AddOverlayLayer(Layer* layer) {
	layerStack.emplace_back(layer);
}

void LayerStack::Update() {
	for (Layer* layer : layerStack) {
		layer->Update();
	}
}

void LayerStack::Draw() {
	for (Layer* layer : layerStack) {
		layer->Draw();
	}
}

bool LayerStack::Create() {
	if (m_instance) LOG_WARNING("An instance of layerstack already exist!");

	m_instance = new LayerStack;
	LOG_INSTANCE("LayerStack created");
	if (!m_instance) return false;

	return true;
}

void LayerStack::Destroy() {
	//Remove GUILayer because it will destroy itself
	//Clear out layerStack
	

	delete m_instance;
	LOG_INSTANCE("LayerStack destroyed");
}