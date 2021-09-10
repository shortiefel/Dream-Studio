/* Start Header**********************************************************************************/
/*
@file    TextureComponent.cpp
@author  
@date    02/07/2021
\brief
This file contain the TextureComponent definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "Engine/Header/Management/ResourceManager.hpp"
//#include "../../External Resources/stb_image/stb_image.h"

namespace Engine {
	Texture::Texture(Entity ID, const std::string path, std::string shape, std::string shader, bool active) :
		IComponent{ ID }, 
		texobj_hdl{ 0 }, filepath{ path }, width{ 0 }, height{ 0 }, BPP{ 0 },
		mdl_ref{ GraphicImplementation::models.find(shape) },
		shd_ref{ GraphicImplementation::shdrpgms.find(shader) },
		isActive{ active }
	{
		// flips image in vertically
		// OpenGL - Cartesian coordinate system
		// PNG - top left
		///stbi_set_flip_vertically_on_load(1);

		// reads and write the width and height into variable, 4 - RBGA
		//unsigned char* 
		////localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);
		//localBuffer = ResourceManager::LoadTexture(filepath, &width, &height, &BPP, 4);
		texobj_hdl = ResourceManager::LoadTexture(filepath, &width, &height, &BPP, 4);
		// checking for error when loading image
		/*if (stbi_failure_reason())
			std::cout << stbi_failure_reason() << std::endl;*/

			// define and initialize a handle to texture object that will
			// encapsulate two-dimensional textures
			//glCreateTextures(GL_TEXTURE_2D, 1, &texobj_hdl);
			//// allocate GPU storage for texture image data loaded from file
			//glTextureStorage2D(texobj_hdl, 1, GL_RGBA8, width, height);
			//// copy image data from client memory to GPU texture buffer memory
			//glTextureSubImage2D(texobj_hdl, 0, 0, 0, width, height,
			//	GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

			// free memory
			/*if (localBuffer)
				stbi_image_free(localBuffer);*/
	}


	Texture::~Texture()
	{
		//Problem is caused by ECS data being copied when moved from one part to another
		//Texture component gets copied and so destroyed afterwards which would cause the texture to be corrupted
		//now done by resourcemanager destroy function
		//glDeleteTextures(1, &texobj_hdl);
	}

	void Texture::Bind(GLuint slot) const
	{
		glBindTextureUnit(slot, texobj_hdl);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		//glActiveTexture(GL_TEXTURE0 + slot);
		//glBindTexture(GL_TEXTURE_2D, texobj_hdl);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}