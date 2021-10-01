/* Start Header**********************************************************************************/
/*!
\file FontSystem.hpp
\team name
\software name
\authors
NAME							EMAIL									ROLE
Goh	See Yong Denise				g.seeyongdenise@digipen.edu
\date 29/06/2021
\brief
FontSystem.hpp: This file contains all the structure and class related to the font systems
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef FONTSYSTEM_H
#define FONTSYSTEM_H

#include "Engine/Header/Graphic/shader.hpp"
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
		long advance;					//offset to advance to next glyph
	};

	class FontSystem
	{
	public:
		void RenderText(std::string text, float x, float y, float scale, const glm::ivec3& colour, float rotation);
		void Init();
		void Draw();

	private:
		std::map<char, Character> characters;
		unsigned int vao, vbo;
		GraphicShader font_shader;
	};
};


#endif /* FontSystem_hpp */