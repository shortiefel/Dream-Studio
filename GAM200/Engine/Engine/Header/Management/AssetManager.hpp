/* Start Header**********************************************************************************/
/*
@file    AssetManager.hpp
@author  Goh See Yong, Denise  	g.seeyongdenise@digipen.edu
@date    29/08/2021
\brief
This file contain the Asset Manager declaration

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include "Engine/Header/pch.hpp"
#include <filesystem>

namespace Engine {

	class AssetManager
	{
	public:
		// Constructor a new Asset Manager
		AssetManager() {};

		// Deconstructor for the Asset Manager
		~AssetManager() { Shutdown(); }

		// Initialize any assets that should be created on start up
		void Init();

		// Clean up any assets
		void Shutdown() {};

		void loadTexture(std::string _name, std::string _fileName);
		//sf::Texture& GetTexture(std::string name);
	private:


	};
}


#endif
