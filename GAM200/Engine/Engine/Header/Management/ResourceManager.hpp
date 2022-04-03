/* Start Header**********************************************************************************/
/*
@file    ResourceManager.hpp
@author  Chia Yi Da		c.yida@digipen.edu	100%
@date    02/07/2021
\brief
This file has the function declaration for ResourceManager


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include "Engine/Header/pch.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"
#include "Engine/Header/Math/MathLib.hpp"

#include "Engine/Header/ECS/Component/UI/UIComponent.hpp"
#include "Engine/Header/ECS/Component/UI/FontComponent.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H

namespace Engine
{
	struct TextureComponent;
	struct ParticleComponent;

	struct TextureContainer
	{
		GLuint texture_handle{};
		int width{}, height{};
	};

	struct CharGlyph
	{
		unsigned int textureid{};	// ID handle of the glyph texture
		Math::ivec2  size{};		// Size of glyph
		Math::ivec2  bearing{};		// Offset from baseline to left/top of glyph
		unsigned int advance{};		// Offset to advance to next glyph (1/64th pixels)
	};

	struct FontContainer
	{
		std::map<char, CharGlyph> characters;
	};

	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		void Create();
		void Destroy();

		void RefreshTexture(TextureComponent* tc);
		void RefreshTexture(ParticleComponent* pc);

		GLuint LoadTexture(std::string filepath);
		GLuint LoadTexture(std::string filepath, int* x, int* y, int* channels_in_files, int desired_channel);

		bool LoadFont(std::string filename);

		TextureContainer GetTextureContainer(std::string name) { return textureList[name]; }
		FontContainer GetFontContainer(std::string filename) { return fontList[filename]; }



		void TextureStbiLoad(TextureComponent& tc, std::string _filepath);
		void TextureStbiLoad(UIComponent& tc, std::string _filepath);
		void TextureStbiLoad(ParticleComponent& tc, std::string _filepath);
		//void FontFTLoad(FontComponent& fc, std::string _filepath);
		void TextureGlfwCreate(TextureComponent& tc);
		void TextureGlfwCreate(UIComponent& tc);
		void TextureGlfwCreate(ParticleComponent& tc);
		//void FontGlfwCreate(FontComponent& tc);

	private:
		GLuint LoadTextureInternal(std::string filename, int* x, int* y, int* channels_in_files, int desired_channel);
		GLuint LoadTextureInternal(std::string filename);

		std::unordered_map<std::string, TextureContainer> textureList;
		std::unordered_map<std::string, FontContainer> fontList;

		SINGLETON_SETUP(ResourceManager);
	};
}

#endif