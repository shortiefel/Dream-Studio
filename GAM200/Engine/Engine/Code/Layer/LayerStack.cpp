/* Start Header**********************************************************************************/
/*
@file    LayerStack.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
@date    16/06/2021
\brief
This file contain LayerStack definition
Layerstacks will hold all the layers and acts sort of like the layer manager
All layers will be updated and drawn properly
Layerstack will settle the ordering of the layers during run time to draw in the correct order


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Layer/LayerStack.hpp"
#include "Engine/Header/Debug Tools/Profiler.hpp"

namespace Engine {
	LayerStack* LayerStack::m_instance = 0;
	std::vector<Layer*> LayerStack::layerStack;
	unsigned int LayerStack::layerCount = 0;

	void LayerStack::AddOverlayLayer(Layer* layer) {
		PROFILER_START("Rendering");

		layerStack.emplace_back(layer);
	}

	void LayerStack::Update() {
		PROFILER_START("Rendering");

		for (Layer* layer : layerStack) {
			layer->Update();
		}
	}

	void LayerStack::Draw() {
		PROFILER_START("Rendering");

		for (Layer* layer : layerStack) {
			layer->Draw();
		}
	}

	bool LayerStack::Create() {
		PROFILER_START("Rendering");

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
}