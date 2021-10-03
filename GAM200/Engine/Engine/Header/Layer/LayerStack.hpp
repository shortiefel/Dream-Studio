/* Start Header**********************************************************************************/
/*
@file    LayerStack.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
@date    16/06/2021
\brief
This file contain LayerStack declaration
Layerstacks will hold all the layers and acts sort of like the layer manager
All layers will be updated and drawn properly
Layerstack will settle the ordering of the layers during run time to draw in the correct order


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/



#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include "Engine/Header/pch.hpp"
#include "Engine/Header/Layer/Layer.hpp"

namespace Engine {
	class LayerStack {
	public:
		//Add layers
		static void AddOverlayLayer(Layer* layer);
		//Remove layers

		static void Update();
		static void Draw();

		static bool Create();
		static void Destroy();

	private:
		static LayerStack* m_instance;
		static std::vector<Layer*> layerStack;
		static unsigned int layerCount; //Not including GUI layer
	};
}

#endif