/* Start Header**********************************************************************************/
/*
@file    ResourceSet.cpp
@author  Chia Yi Da		c.yida@digipen.edu		100%
@date    29/10/2021
@brief
This file contain a texture setter


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Graphic/ResourceSet.hpp"
#include "Engine/Header/Management/ResourceManager.hpp"

// MACROS
#define SET_TEXTURE(filepath, textureName, texobj_hdl)  if (_filepath.empty()) return;\
														filepath = _filepath.substr(_filepath.rfind("Assets"));\
														textureName = filepath.substr(filepath.find_last_of("\\") + 1);\
														textureName = textureName.substr(0, textureName.find_last_of("."));\
														texobj_hdl = ResourceManager::GetInstance().LoadTexture(filepath, &width, &height, &BPP, 4);

#define SET_FONT(filepath, fontName, isFont)			if (_filepath.empty()) return;\
														filepath = _filepath.substr(_filepath.rfind("Assets"));\
														fontName = filepath.substr(filepath.find_last_of("\\") + 1);\
														fontName = fontName.substr(0, fontName.find_last_of("."));\
														isFont = ResourceManager::GetInstance().LoadFont(filepath);

namespace Engine
{
	namespace GraphicImplementation
	{
		// Function that load texture and set variables to Texture Component
		void SetTexture(TextureComponent* _texptr, std::string _filepath)
		{
			std::string& filepath = _texptr->filepath;
			std::string& textureName = _texptr->textureName;
			GLuint& texobj_hdl = _texptr->texobj_hdl;

			GLint& width = _texptr->width;
			GLint& height = _texptr->height;
			GLint& BPP = _texptr->BPP;

			SET_TEXTURE(filepath, textureName, texobj_hdl);
		}

		// Function that load texture and set variables to Particle Component
		void SetTexture(ParticleComponent* _texptr, std::string _filepath)
		{
			std::string& filepath = _texptr->filepath;
			std::string& textureName = _texptr->textureName;
			GLuint& texobj_hdl = _texptr->texobj_hdl;

			GLint& width = _texptr->width;
			GLint& height = _texptr->height;
			GLint& BPP = _texptr->BPP;

			SET_TEXTURE(filepath, textureName, texobj_hdl);
		}

		// Function that load texture and set variables to UI Component
		void SetTexture(UIComponent* _texptr, std::string _filepath)
		{
			std::string& filepath = _texptr->filepath;
			std::string& textureName = _texptr->textureName;
			GLuint& texobj_hdl = _texptr->texobj_hdl;

			GLint width;
			GLint height;
			GLint BPP;

			SET_TEXTURE(filepath, textureName, texobj_hdl);
		}

		// Function that load fonts and set variables to Font component
		void SetFont(FontComponent* _texptr, std::string _filepath)
		{
			std::string& filepath = _texptr->filepath;
			std::string& fontName = _texptr->fontName;

			bool& isFont = _texptr->isFont;

			SET_FONT(filepath, fontName, isFont);
		}
	}
}