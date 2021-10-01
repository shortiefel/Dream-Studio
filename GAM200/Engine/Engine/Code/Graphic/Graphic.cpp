/* Start Header**********************************************************************************/
/*
@file    Graphic.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
         Chia Yi Da		chiayida98@gmail.com
@date    16/06/2021
\brief
This file has the function definition for Graphic


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug tools/Logging.hpp" 
#include "Engine/Header/Graphic/Graphic.hpp" 
#include "Engine/Header/Window.hpp" 

#include "Engine/Header/Management/Settings.hpp"

#include <iostream>
#include <fstream>

namespace Engine {
    namespace GraphicImplementation {
        //Frame buffer index
        unsigned int fbo;
        bool fbo_exist = false;

        std::map<GraphicShape, GLModel> models;
        std::map<GraphicShader, GLSLShader> shdrpgms;
        GLuint Setup_Texobj(std::string, GLuint, GLuint);



        void CreateFramebuffer(GLsizei width, GLsizei height, unsigned int* framebuffer, unsigned int* texColorBuffer) {

            glGenFramebuffers(1, framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, *framebuffer);

            glGenTextures(1, texColorBuffer);
            glBindTexture(GL_TEXTURE_2D, *texColorBuffer);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);

            //Attach texture to framebuffer object
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *texColorBuffer, 0);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                LOG_ERROR("Error: Framebuffer is not complete");
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void DeleteFramebuffer(unsigned int f) {
            glDeleteFramebuffers(1, &f);
        }

        void SetFramebuffer(unsigned int f, bool exist) {
            if (!exist) {
                fbo_exist = false;
                return;
            }

            fbo_exist = true;
            fbo = f;
        }

        void BindFramebuffer() {
            if (fbo_exist)
                glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        }

        void UnbindFramebuffer() {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void UseShaderHandle(unsigned int prgm_handle) {
            glUseProgram(prgm_handle);
        }

        void UnUseShaderHandle() {
            glUseProgram(0);
        }
    }
}