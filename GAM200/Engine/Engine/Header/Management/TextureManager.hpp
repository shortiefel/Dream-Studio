/* Start Header**********************************************************************************/
/*
@file    TextureManager.hpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    03/07/2021
\brief
This file has the function declaration for TextureManager


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "Engine/Header/pch.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"

namespace Engine
{
	struct sTexture
	{
		GLuint handle;
		int width, height;
	};


	class TextureManager : public Singleton<TextureManager>
	{
	public:
		void Create();
		void Destroy();
		GLuint LoadTexture(std::string filename, int* x, int* y, int* channels_in_files, int desired_channel, bool isTexture = true);
	private:
		std::unordered_map<std::string, sTexture> textureList;

		SINGLETON_SETUP(TextureManager);
	};
}

#endif