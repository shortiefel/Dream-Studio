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

#include "Engine/Header/Graphic/Graphic.hpp" 
#include "Engine/Header/ECS/System/GraphicSystem.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/Graphic/FrameBuffer.hpp"
#include "Engine/Header/ECS/System/CameraSystem.hpp"
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

	class FontSystem : public Singleton<FontSystem>
	{
	public:

		void RenderText(GLuint shader, std::string text, float x, float y, float scale, const glm::vec3& colour);

		bool Create();
		void Destroy();

		void Render(Math::mat3 camMatrix = CameraSystem::GetInstance().GetTransform(), Graphic::FrameBuffer* _fbo = nullptr);

	private:
		std::map<char, Character> characters;
		unsigned int vao, vbo;
		GLSLShader* font_shader;
		GLSLShader shader;

		SINGLETON_SETUP(FontSystem);
	};
};


#endif /* FontSystem_hpp */