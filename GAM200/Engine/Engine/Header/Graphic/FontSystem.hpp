/* Start Header**********************************************************************************/
/*!
@file FontSystem.hpp
@authors	Goh See Yong Denise				g.seeyongdenise@digipen.edu
@date 29/06/2021
@brief
FontSystem.hpp: This file contains all the structure and class related to the font systems

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef FONTSYSTEM_HPP
#define FONTSYSTEM_HPP

#include "Engine/Header/Graphic/Shader.hpp"
#include "Engine/Header/Graphic/GLSLShader.hpp"
#include "Engine/Header/Graphic/Graphic.hpp" 
#include <glm/glm.hpp>
#include <map>
#include <string>

namespace Engine
{
	struct Character
	{
		unsigned int texture_ID;		//ID hadle of the texture
		glm::ivec2 size;				//Size of glyph
		glm::ivec2 bearing;				//Offset from baseline to left/top of glyph
		long advance;					//Horizontal offset to advance to next glyph
	};

	class FontSystem
	{
	public:
		FontSystem() = default;
		~FontSystem();
		void RenderText(GLSLShader &shader, std::string text, float x, float y, float scale, const glm::ivec3& colour, float rotation);
		void Init();
		void Draw();
		bool Load(std::string path);
		void Unload();

	private:
		std::map<char, Character> characters;
		unsigned int vao, vbo;
		GLSLShader font_shader;
	};
};


#endif /* FontSystem_hpp */