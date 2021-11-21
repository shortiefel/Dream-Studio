/* Start Header**********************************************************************************/
/*
@file    FrameBuffer.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu   	100%
@date    17/10/2021
\brief
This file has the function definition for class FrameBuffer


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug tools/Logging.hpp" 
#include "Engine/Header/Graphic/FrameBuffer.hpp"
#include <iostream>
namespace Engine {
	namespace Graphic {
        void FrameBuffer::Create(GLsizei _width, GLsizei _height) {
            width = _width;
            height = _height;

            glGenFramebuffers(1, &fbo_index);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo_index);

            unsigned int* tex_ptr = reinterpret_cast<unsigned int*>(&fbo_texture);
            glGenTextures(1, tex_ptr);
            glBindTexture(GL_TEXTURE_2D, *tex_ptr);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glBindTexture(GL_TEXTURE_2D, 0);

            //Attach texture to framebuffer object
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *tex_ptr, 0);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                LOG_ERROR("Error: Framebuffer is not complete");
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        FrameBuffer::~FrameBuffer() {
            glDeleteFramebuffers(1, &fbo_index);
        }

        void FrameBuffer::Resize(GLsizei _width, GLsizei _height) {
            if (width == _width && height == _height) return;

            /*float ar = static_cast<float>(_width) / _height;
            height = static_cast<GLsizei>(width / ar);*/
            width = _width;
            height = _height;
            unsigned int* tex_ptr = reinterpret_cast<unsigned int*>(&fbo_texture);
            glBindTexture(GL_TEXTURE_2D, *tex_ptr);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, NULL);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        int FrameBuffer::ReadPixel(int x, int y) const {
            glReadBuffer(fbo_index);

            int pixel;
            glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixel);
            return pixel;
        }

        void FrameBuffer::Bind() {
            glBindFramebuffer(GL_FRAMEBUFFER, fbo_index);
        }

        void FrameBuffer::Unbind() {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void FrameBuffer::Bind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, fbo_index);
        }

        void FrameBuffer::Unbind() const {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        unsigned int FrameBuffer::GetIndex() const {
            return fbo_index;
        }

        const ImTextureID& FrameBuffer::GetTexture() const {
            return fbo_texture;
        }
	}
}