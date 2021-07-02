#include <Component/Graphics/TextureComponent.hpp>
#include "../../External Resources/stb_image/stb_image.h"

Texture::Texture(const std::string& path) : 
	texobj_hdl{0}, filepath{path}, localBuffer{nullptr}, width{0}, height{0}, BPP{0} 
{
	// flips image in vertically
	// OpenGL - Cartesian coordinate system
	// PNG - top left
	stbi_set_flip_vertically_on_load(1);

	// reads and write the width and height into variable, 4 - RBGA
	localBuffer = stbi_load(filepath.c_str(), &width, &height, &BPP, 4);

	// checking for error when loading image
	//if (stbi_failure_reason())
	//	std::cout << stbi_failure_reason() << std::endl;

	// binds texture
	glCreateTextures(GL_TEXTURE_2D, 1, &texobj_hdl);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// allocate GPU storage for texture image data loaded from file
	glTextureStorage2D(texobj_hdl, 1, GL_RGBA8, width, height);

	// copy image data from client memory to GPU texture buffer memory
	glTextureSubImage2D(texobj_hdl, 0, 0, 0, width, height,
		GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

	// free memory
	if (localBuffer) 
		stbi_image_free(localBuffer);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texobj_hdl);
}

void Texture::Bind(GLuint slot) const
{
	glBindTextureUnit(slot, texobj_hdl);

	//glActiveTexture(GL_TEXTURE0 + slot);
	//glBindTexture(GL_TEXTURE_2D, texobj_hdl);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}