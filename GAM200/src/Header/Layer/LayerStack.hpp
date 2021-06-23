//Layerstacks will hold all the layers and acts sort of like the layer manager
//All layers will be updated and drawn properly 
//Layerstack will settle the ordering of the layers during run time to draw in the correct order

#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include "pch.hpp"
#include "Layer.hpp"

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

#endif