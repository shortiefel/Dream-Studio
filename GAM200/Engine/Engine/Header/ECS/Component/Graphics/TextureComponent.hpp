/* Start Header**********************************************************************************/
/*
@file    TextureComponent.hpp
@author
@date    02/07/2021
\brief
This file contain the TextureComponent declaration

//Serialize list
-string: pathname


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef TEXTURE_COMPONENT_HPP
#define TEXTURE_COMPONENT_HPP

#include "Engine/Header/Graphic/glslshader.hpp" // for GLSLShader
#include "Engine/Header/pch.hpp"
#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/ECS/Component/IComponent.hpp"

namespace Engine {
	class Texture : public IComponent {
	public:
		Texture(Entity ID, const std::string path, std::string shape = "Square", std::string shader = "Default", bool active = true);
		Texture() = default;
		Texture(const Texture&) = default;
		Texture& operator= (const Texture&) = default;
		~Texture();

		void Bind(GLuint slot = 0) const;
		void Unbind() const;

		inline GLint getWidth() const { return width; }
		inline GLint getHeight() const { return height; }
		inline GLuint getTexObj() const { return texobj_hdl; }
		inline std::string getFilepath() const { return filepath; }
		inline bool GetActive() const { return isActive; }
		inline std::map<std::string, GraphicImplementation::GLModel>::iterator get_mdl_ref() const { return mdl_ref; }
		inline std::map<std::string, GLSLShader>::iterator get_shd_ref() const { return shd_ref; }


	private:
		GLuint texobj_hdl = GLuint{};

		std::string filepath = "";

		std::map<std::string, GraphicImplementation::GLModel>::iterator mdl_ref = GraphicImplementation::models.begin();
		std::map<std::string, GLSLShader>::iterator shd_ref = GraphicImplementation::shdrpgms.begin();

		bool isActive = true;

		GLint width = GLint{}, height = GLint{}, BPP = GLint{}; //BPP - bits per pixel
	};
}

#endif