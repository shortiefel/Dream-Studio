/* Start Header**********************************************************************************/
/*
@file    TextureManager.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    03/07/2021
\brief
This file has the function definition for TextureManager


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Management/TextureManager.hpp"
#include "stb_image/stb_image.h"

namespace Engine 
{
	//std::unordered_map<std::string, GLuint> TextureManager::textureList;

	void TextureManager::Create() 
	{
		// flips image in vertically
		// OpenGL - Cartesian coordinate system
		// PNG - top left
		stbi_set_flip_vertically_on_load(1);

		LOG_INSTANCE("TextureManager created");
	}

	void TextureManager::Destroy() 
	{
		for (auto& a : textureList) 
		{
			glDeleteTextures(1, &a.second);
		}

		LOG_INSTANCE("TextureManager destroyed");
	}

	GLuint TextureManager::LoadTexture(std::string filename, int* x, int* y, int* channels_in_files, int desired_channel) 
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
}