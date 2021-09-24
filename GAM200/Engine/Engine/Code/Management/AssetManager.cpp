/* Start Header**********************************************************************************/
/*
@file    AssetManager.cpp
@author  Goh See Yong, Denise  	g.seeyongdenise@digipen.edu
@date    29/08/2021
\brief
This file has the function definition for AssetManager


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Management/AssetManager.hpp"
#include "Engine/Header/Management/TextureManager.hpp"
#include <iostream>
#include <fstream>

namespace Engine
{
	void AssetManager::Init()
	{
		LOG_INSTANCE("AssetManager created");

	}

	void AssetManager::Shutdown()
	{
		LOG_INSTANCE("AssetManager destroyed");
	}

	void AssetManager::LoadFont(std::string name, std::string fileName)
	{
		std::string fontsPath = "./Assets/Fonts";

		//to add after fixing font system
	}

}