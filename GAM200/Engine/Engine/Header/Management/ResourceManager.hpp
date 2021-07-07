/* Start Header**********************************************************************************/
/*
@file    ResourceManager.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    03/07/2021
\brief
This file has the function declaration for resourcemanager


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef RESOURCE_MANAGER_HPP
#define RESOUCE_MANAGER_HPP

#include "pch.hpp"

class ResourceManager {
public:
	static void Create();
	static void Destroy();
	static GLuint LoadTexture(std::string filename, int* x, int* y, int* channels_in_files, int desired_channel);
private:
	static std::unordered_map<std::string, GLuint> textureList;
};

#endif