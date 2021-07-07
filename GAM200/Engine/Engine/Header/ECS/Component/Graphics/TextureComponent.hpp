/* Start Header**********************************************************************************/
/*
@file    TextureComponent.hpp
@author
@date    02/07/2021
\brief
This file contain the TextureComponent declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef TEXTURE_COMPONENT_HPP
#define TEXTURE_COMPONENT_HPP

#include "Graphic/glslshader.hpp" // for GLSLShader
#include "pch.hpp"

class Texture {
public:
	Texture(const std::string);
	Texture() = default;
	Texture(const Texture&) = default;
	Texture& operator= (const Texture&) = default;
	~Texture();

	void Bind(GLuint slot = 0) const;
	void Unbind() const;
	
	inline GLint getWidth() const { return width; }
	inline GLint getHeight() const { return height; }
	inline GLuint getTexObj() const { return texobj_hdl; }

private:
	GLuint texobj_hdl = GLuint{};
	//I dont think u need to store anything below this line
	std::string filepath = "";
	
	GLint width = GLint{}, height = GLint{}, BPP = GLint{}; //BPP - bits per pixel
};

#endif