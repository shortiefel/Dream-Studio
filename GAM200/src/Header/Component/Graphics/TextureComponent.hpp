#ifndef TEXTURE_COMPONENT_HPP
#define TEXTURE_COMPONENT_HPP

#include "Graphic/glslshader.hpp" // for GLSLShader
#include "pch.hpp"

class Texture {
public:
	Texture(const std::string&);
	~Texture();

	void Bind(GLuint slot = 0) const;
	void Unbind() const;
	
	inline GLint getWidth() const { return width; }
	inline GLint getHeight() const { return height; }
	inline GLuint getTexObj() const { return texobj_hdl; }

private:
	GLuint texobj_hdl;
	std::string filepath;
	unsigned char* localBuffer;
	GLint width, height, BPP; //BPP - bits per pixel
};

#endif