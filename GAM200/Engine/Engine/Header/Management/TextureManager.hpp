/* Start Header**********************************************************************************/
/*
@file    TextureManager.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

namespace Engine {
	class TextureManager {
	public:
		static void Create();
		static void Destroy();
		static GLuint LoadTexture(std::string filename, int* x, int* y, int* channels_in_files, int desired_channel);
	private:
		static std::unordered_map<std::string, GLuint> textureList;
	};
}

#endif