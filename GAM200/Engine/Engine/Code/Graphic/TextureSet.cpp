/* Start Header**********************************************************************************/
/*
@file    TextureSet.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    29/10/2021
@brief
This file contain a texture setter


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Graphic/TextureSet.hpp"

#include "Engine/Header/Management/TextureManager.hpp"

#define SET_TEXTURE(filepath, textureName, texobj_hdl)  if (_filepath.empty()) return;\
														filepath = _filepath.substr(_filepath.rfind("Assets"));\
														textureName = filepath.substr(filepath.find_last_of("\\") + 1);\
														textureName = textureName.substr(0, textureName.find_last_of("."));\
														texobj_hdl = TextureManager::GetInstance().LoadTexture(filepath, &width, &height, &BPP, 4);

namespace Engine {
	namespace GraphicImplementation {
		void SetTexture(TextureComponent* _texptr, std::string _filepath) {
			std::string& filepath = _texptr->filepath;
			std::string& textureName = _texptr->textureName;
			GLuint& texobj_hdl = _texptr->texobj_hdl;
			GLint& width = _texptr->width;
			GLint& height = _texptr->height;
			GLint& BPP = _texptr->BPP;

			SET_TEXTURE(filepath, textureName, texobj_hdl);
		}

		void SetTexture(UIComponent* _texptr, std::string _filepath) {
			std::string& filepath = _texptr->filepath;
			std::string& textureName = _texptr->textureName;
			GLuint& texobj_hdl = _texptr->texobj_hdl;
			GLint width;
			GLint height;
			GLint BPP;

			SET_TEXTURE(filepath, textureName, texobj_hdl);
		}
	}
}
