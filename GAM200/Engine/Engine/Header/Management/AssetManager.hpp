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
#include "Engine/Header/Management/TextureManager.hpp"
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

		GLuint LoadTexture(std::string filename, int* x, int* y, int* channels_in_files, int desired_channel);

		GLuint LoadFont(std::string filename, int* x, int* y, int* channels_in_files, int desired_channel);

		//void addResource(Resource* resource, const std::string& name, const std::string& path);

		//template <typename T>
		//T* getResource(const std::string& name)
		//{
		//	return dynamic_cast<T * resources.find(name)->second);
		//}

		//static const std::vector<Texture>& GetAllTextures() { return textureList; }
		bool AddNewFontAssets(const std::string _fontlist);

		FontSystem* GetFontAssets(const std::string& _name);
		void ClearAllAssets();
	private:
		std::unordered_map<std::string, GLuint> textureList;

		std::unordered_map<std::string, GLuint> fontList;

		//std::map<std::string, Resource*> resources;

		SINGLETON_SETUP(AssetManager);
	};
}


#endif
