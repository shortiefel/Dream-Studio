/* Start Header**********************************************************************************/
/*
@file    AssetManager.hpp
@author  Goh See Yong, Denise  	g.seeyongdenise@digipen.edu	100%
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
#include "Engine/Header/Management/ResourceManager.hpp"
#include "Engine/Header/ECS/System/FontSystem.hpp"
#include <filesystem>
#include <string>
#include <unordered_map>
#include <memory>

namespace Engine {

	class AssetManager : public Singleton<AssetManager>
	{
	public:
		// Initialize any assets that should be created on start up
		void Init();


		void Create();

		// Clean up any assets
		void Destroy();

		GLuint LoadTexture(std::string _filename, int* x, int* y, int* channels_in_files, int desired_channel);

		bool LoadFont(std::string _filename);

		//bool AddNewFontAssets(const std::string _fontlist);
		void UpdateList();

		FontContainer GetFontContainer(std::string _filename) { return fontList[_filename]; }

		void ClearAllAssets();

	private:
		GLuint LoadTextureInternal(std::string filename, int* x, int* y, int* channels_in_files, int desired_channel);

		std::unordered_map<std::string, TextureContainer> textureList;

		std::unordered_map<std::string, FontContainer> fontList;

		std::string _assetdirection;

		std::vector<std::string> assetList;

		SINGLETON_SETUP(AssetManager);
	};
}


#endif