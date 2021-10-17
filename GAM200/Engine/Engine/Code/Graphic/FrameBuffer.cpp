/* Start Header**********************************************************************************/
/*
@file    FrameBuffer.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

namespace Engine {
	namespace Graphic {
        void FrameBuffer::Create(GLsizei width, GLsizei height) {

            glGenFramebuffers(1, &fbo_index);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo_index);

            unsigned int* tex_ptr = reinterpret_cast<unsigned int*>(&fbo_texture);
            glGenTextures(1, tex_ptr);
            glBindTexture(GL_TEXTURE_2D, *tex_ptr);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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