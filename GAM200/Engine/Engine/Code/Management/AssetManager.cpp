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
		stbi_set_flip_vertically_on_load(1);
		LOG_INSTANCE("AssetManager created");
	}

	void AssetManager::Destroy()
	{
		// For textures
		for (auto& a : textureList)
		{
			glDeleteTextures(1, &a.second.texture_handle);
		}
		textureList.clear();

		// For fonts
		for (auto& b : fontList)
		{
			for (auto& c : b.second.characters)
			{
				glDeleteTextures(1, &c.second.textureid);
			}
		}
		fontList.clear();
		LOG_INSTANCE("AssetManager destroyed");
	}

	// Function loads texture into container without checking if it exist
	GLuint AssetManager::LoadTextureInternal(std::string filename, int* x, int* y, int* channels_in_files, int desired_channel)
	{

		//using ResourceManager LoadTextureInternal
		// Read png file
		stbi_uc* temBuff = stbi_load(filename.c_str(), x, y, channels_in_files, desired_channel);

		GLuint texobj_hdl{};
		glCreateTextures(GL_TEXTURE_2D, 1, &texobj_hdl);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTextureStorage2D(texobj_hdl, 1, GL_RGBA8, *x, *y);
		glTextureSubImage2D(texobj_hdl, 0, 0, 0, *x, *y, GL_RGBA, GL_UNSIGNED_BYTE, temBuff);

		glBindTexture(GL_TEXTURE_2D, 0);

		if (temBuff) stbi_image_free(temBuff);

		// Store in container to be reused later
		textureList[filename].texture_handle = texobj_hdl;
		textureList[filename].width = *x;
		textureList[filename].height = *y;

		return textureList[filename].texture_handle;
	}

	GLuint AssetManager::LoadTexture(std::string _filename, int* x, int* y, int* channels_in_files, int desired_channel)
	{
		//using ResourceManager LoadTexture
		return ResourceManager::GetInstance().LoadTexture(_filename, x, y, channels_in_files, desired_channel);
	}


	bool AssetManager::LoadFont(std::string _filename)
	{
		//using ResourceManager LoadFont
		return ResourceManager::GetInstance().LoadFont(_filename);
	}

	void AssetManager::UpdateList()
	{

	}

}