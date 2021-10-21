/* Start Header**********************************************************************************/
/*
@file    FrameBuffer.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    17/10/2021
\brief
#include "Engine/Header/Graphic/FrameBuffer.hpp"
This file has the function declaration for class FrameBuffer


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef FRAME_BUFFER
#define FRAME_BUFFER

#include "Engine/Header/pch.hpp"
#include <Imgui/imgui_impl_glfw.h>


namespace Engine {
	namespace Graphic {
		class FrameBuffer {
		public:
			FrameBuffer() = default;
			void Create(GLsizei _width, GLsizei _height);
			~FrameBuffer();

			//Resize based on aspect ratio
			void Resize(GLsizei _width, GLsizei _height);
			int ReadPixel(int x, int y) const;

			void Bind();
			void Unbind();
			void Bind() const;
			void Unbind() const;

			unsigned int GetIndex() const;
			const ImTextureID& GetTexture() const;
		private:
			unsigned int fbo_index;
			ImTextureID fbo_texture;
			GLsizei width; 
			GLsizei height;
		};
	}
}

#endif