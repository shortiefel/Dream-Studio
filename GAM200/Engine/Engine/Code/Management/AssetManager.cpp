/* Start Header**********************************************************************************/
/*
@file    AssetManager.cpp
@author  Goh See Yong, Denise  	g.seeyongdenise@digipen.edu		100%
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
#include "stb_image/stb_image.h"
#include <iostream>
#include <fstream>

namespace Engine
{
	void AssetManager::Init()
	{
		std::string audiosPath = "./Assets/Audio";
		std::string fontsPath = "./Assets/Fonts";
		std::string shadersPath = "./Assets/Shaders";
		std::string scenesPath = "./Assets/Scenes/Scenes";

		typedef std::map<std::string, std::string> namePath;

		namePath resourselist;

		typedef std::unordered_map<std::string, std::string> name_path_unordered;

		name_path_unordered resourseList;

		//to add audio file directory
		std::vector<std::string> texturesPath;

		texturesPath.push_back("./Assets/Textures");
	}
	void AssetManager::Create()
	{
		LOG_INSTANCE("AssetManager created");
	}

	void AssetManager::Destroy()
	{
		LOG_INSTANCE("AssetManager destroyed");
	}

	GLuint AssetManager::LoadTexture(std::string filename, int* x, int* y, int* channels_in_files, int desired_channel)
	{
		//Check if it exist first before loading
		if (textureList.find(filename) != textureList.end()) return textureList[filename];

		stbi_uc* temBuff = stbi_load(filename.c_str(), x, y, channels_in_files, desired_channel);

		GLuint texobj_hdl;

		// define and initialize a handle to texture object that will
		// encapsulate two-dimensional textures
		glCreateTextures(GL_TEXTURE_2D, 1, &texobj_hdl);

		// allocate GPU storage for texture image data loaded from file
		glTextureStorage2D(texobj_hdl, 1, GL_RGBA8, *x, *y);

		// copy image data from client memory to GPU texture buffer memory
		glTextureSubImage2D(texobj_hdl, 0, 0, 0, *x, *y, GL_RGBA, GL_UNSIGNED_BYTE, temBuff);

		if (temBuff)
		{
			stbi_image_free(temBuff);
		}

		//store in a container to be reused later
		textureList[filename] = texobj_hdl;
		return textureList[filename];
	}

	GLuint AssetManager::LoadFont(std::string filename, int* x, int* y, int* channels_in_files, int desired_channel)
	{
		//Check if it exist first before loading
		if (fontList.find(filename) != fontList.end()) return fontList[filename];

		stbi_uc* temBuff = stbi_load(filename.c_str(), x, y, channels_in_files, desired_channel);

		GLuint fontobj_hdl;

		// define and initialize a handle to texture object that will
		// encapsulate two-dimensional textures
		glCreateTextures(GL_TEXTURE_2D, 1, &fontobj_hdl);

		// allocate GPU storage for texture image data loaded from file
		glTextureStorage2D(fontobj_hdl, 1, GL_RGBA8, *x, *y);

		// copy image data from client memory to GPU texture buffer memory
		glTextureSubImage2D(fontobj_hdl, 0, 0, 0, *x, *y, GL_RGBA, GL_UNSIGNED_BYTE, temBuff);

		if (temBuff)
		{
			stbi_image_free(temBuff);
		}

		//store in a container to be reused later
		fontList[filename] = fontobj_hdl;
		return fontList[filename];

	}

	//void AssetManager::addResource(Resource* resource, const std::string& name, const std::string& path)
	//{
	//	//resource->getResourcePath(path);
	//	//resource->getResourceId(mResources.size());
	//	resource->loadResource();

	//	mResources.insert(std::pair<std::string, Resource*>(name, resource));
	//}
	//with sfml graphic test later
	//void AssetManager::loadTexture(std::string name, std::string fileName)
	//{
	//	sf::Texture tex;
	//	if (tex.loadFromFile(fileName))
	//	{
	//		this->textures_[name] = tex;
	//	}
	//}

	//sf::Texture& AssetManager::GetTexture(std::string name)
	//{
	//	return this->textures_.at(name);
	//}

	//void AssetManager::loadFont(std::string name, std::string fileName)
	//{
	//	sf::Font font;
	//	if (font.loadFromFile(fileName))
	//	{
	//		this->fonts_[name] = font;
	//	}
	//}

	//sf::Font& AssetManager::GetFont(std::string name)
	//{
	//	return this->fonts_.at(name);
	//}

}