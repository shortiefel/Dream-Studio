/* Start Header**********************************************************************************/
/*
@file    ResourceManager.cpp
@author  Chia Yi Da		c.yida@digipen.edu		100%
@date    02/07/2021
\brief
This file has the function definition for ResourceManager


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/Management/ResourceManager.hpp"
#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/ParticleComponent.hpp"

#include "stb_image/stb_image.h"

namespace Engine
{
	// Create function for ResourceManager
	void ResourceManager::Create()
	{
		// OpenGL - Cartesian coordinate system
		// Flips image in vertically; PNG - top left
		stbi_set_flip_vertically_on_load(1);

		LOG_INSTANCE("ResourceManager created");
	}

	// Destroy function for ResourceManager
	void ResourceManager::Destroy()
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

		LOG_INSTANCE("ResourceManager destroyed");
	}

	// Function that reloads the texture after it has been updated
	// Overloading for TextureComponent and Particlecomponent
	void ResourceManager::RefreshTexture(TextureComponent* tc) 
	{
		TextureComponent& texture = *tc;
		stbi_uc* temBuff = stbi_load(texture.filepath.c_str(), &(texture.width), &(texture.height), &(texture.BPP), 4);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTextureSubImage2D(textureList[texture.filepath].texture_handle, 0, 0, 0, (texture.width), (texture.height), GL_RGBA, GL_UNSIGNED_BYTE, temBuff);
		stbi_image_free(temBuff);
	}

	void ResourceManager::RefreshTexture(ParticleComponent* pc)
	{
		ParticleComponent& texture = *pc;
		stbi_uc* temBuff = stbi_load(texture.filepath.c_str(), &(texture.width), &(texture.height), &(texture.BPP), 4);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTextureSubImage2D(textureList[texture.filepath].texture_handle, 0, 0, 0, (texture.width), (texture.height), GL_RGBA, GL_UNSIGNED_BYTE, temBuff);
		stbi_image_free(temBuff);
	}

	// Function loads texture into container without checking if it exist
	GLuint ResourceManager::LoadTextureInternal(std::string filename, int* x, int* y, int* channels_in_files, int desired_channel) 
	{
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

	// Function loads texture into container without checking if it exist
	GLuint ResourceManager::LoadTextureInternal(std::string filename) 
	{
		int width = 0, height = 0, BPP = 0;

		int* x = &width;
		int* y = &height;
		int* channels_in_files = &BPP;

		// Read png file
		stbi_uc* temBuff = stbi_load(filename.c_str(), x, y, channels_in_files, 4);

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

	// Function loads texture into container if it doesnt exist
	GLuint ResourceManager::LoadTexture(std::string filepath, int* x, int* y, int* channels_in_files, int desired_channel)
	{
		// Check if it exist first before loading
		if (textureList.find(filepath) != textureList.end())
		{
			*x = textureList[filepath].width;
			*y = textureList[filepath].height;

			return textureList[filepath].texture_handle;
		}

		return LoadTextureInternal(filepath, x, y, channels_in_files, desired_channel);
	}

	// Function loads texture into container if it doesnt exist
	GLuint ResourceManager::LoadTexture(std::string filepath)
	{
		// Check if it exist first before loading
		if (textureList.find(filepath) != textureList.end())
		{
			return textureList[filepath].texture_handle;
		}

		return LoadTextureInternal(filepath);
	}

	// Function loads font into container
	bool ResourceManager::LoadFont(std::string filename)
	{
		//Check if it exist first before loading
		if (fontList.find(filename) != fontList.end())
		{
			return true;
		}

		// Initialise library
		FT_Library ft_library;
		if (FT_Init_FreeType(&ft_library))
		{
			std::cout << "ERROR::FREETYPE: LIBRARY INITIALIZATION: "
				<< filename << std::endl;

			return false;
		}

		// Load font
		FT_Face newface;
		if (FT_New_Face(ft_library, filename.c_str(), 0, &newface))
		{
			std::cout << "ERROR::FREETYPE: FAIL TO LOAD FONT: "
				<< filename << std::endl;

			return false;
		}

		FT_Set_Pixel_Sizes(newface, 0, 80); // 0 for width -> dynamically resize.

		// Load texture

		// Disable byte alignment restriction, 1 byte for each pixel
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// ASCII Table, 32 onwards for alphabets and symbols
		for (unsigned char c = 32; c < 128; c++)
		{
			// Load glyph 
			if (FT_Load_Char(newface, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: FAIL TO LOAD GLYPH: " << filename
					<< " ASCII number: " << c << std::endl;
				continue;
			}

			//GL_RED -> one color channel
			GLuint texobj_hdl;
			glGenTextures(1, &texobj_hdl);
			glBindTexture(GL_TEXTURE_2D, texobj_hdl);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
				newface->glyph->bitmap.width, newface->glyph->bitmap.rows,
				0, GL_RED, GL_UNSIGNED_BYTE, newface->glyph->bitmap.buffer);

			// Set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// Store character for later use
			fontList[filename].characters[c] = { texobj_hdl,
				Math::ivec2(newface->glyph->bitmap.width, newface->glyph->bitmap.rows),
				Math::ivec2(newface->glyph->bitmap_left, newface->glyph->bitmap_top),
				(unsigned int)newface->glyph->advance.x };
		}

		// Clear FreeType resources
		FT_Done_Face(newface);
		FT_Done_FreeType(ft_library);

		return true;
	}
}
// Code that might be used for the future

/*
	//glCreateTextures(GL_TEXTURE_2D, 1, &texobj_hdl);
	glGenTextures(1, &texobj_hdl);
	glBindTexture(GL_TEXTURE_2D, texobj_hdl);

	// allocate GPU storage for texture image data loaded from file
	//glTextureStorage2D(texobj_hdl, 1, GL_RGBA8, *x, *y);
	//glTextureStorage2D(texobj_hdl, 1, GL_R32I, *x, *y);
	//glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA8, *x, *y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, *x, *y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	// copy image data from client memory to GPU texture buffer memory
	//glTextureSubImage2D(texobj_hdl, 0, 0, 0, *x, *y, GL_RGBA, GL_UNSIGNED_BYTE, temBuff);
	//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, *x, *y, GL_RGB, GL_UNSIGNED_BYTE, temBuff);
*/