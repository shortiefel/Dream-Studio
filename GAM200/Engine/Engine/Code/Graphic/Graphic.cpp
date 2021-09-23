/* Start Header**********************************************************************************/
/*
@file    Graphic.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
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

#include <iostream>
#include <fstream>

namespace Engine {
    namespace GraphicImplementation {
        //Frame buffer index
        unsigned int fbo;
        bool fbo_exist = false;

        std::map<std::string, GLModel> models;
        std::map<std::string, GLSLShader> shdrpgms;
        GLuint Setup_Texobj(std::string, GLuint, GLuint);

        void setup_shdr() {
            // Default Shader for Objects
            std::vector<std::pair<GLenum, std::string>> shdr_files1{ 
            std::make_pair(GL_VERTEX_SHADER, "Assets/Shaders/OpenGLEngine.vert"),
            std::make_pair(GL_FRAGMENT_SHADER, "Assets/Shaders/OpenGLEngine.frag") };

            GLSLShader shdr_pgm1;
            shdr_pgm1.CompileLinkValidate(shdr_files1);

            if (GL_FALSE == shdr_pgm1.IsLinked()) {
                std::cout << "Unable to compile/link/validate shader programs\n";
                std::cout << shdr_pgm1.GetLog() << "\n";
                std::exit(EXIT_FAILURE);
            }

            shdrpgms.insert(std::pair<std::string, GLSLShader>("Default", shdr_pgm1));

            // Stencil Shader for debug draw
            std::vector<std::pair<GLenum, std::string>> shdr_files2 { 
            std::make_pair(GL_VERTEX_SHADER, "Assets/Shaders/OpenGLEngine.vert"),
            std::make_pair(GL_FRAGMENT_SHADER, "Assets/Shaders/fStencilTesting.frag") };

            GLSLShader shdr_pgm2;
            shdr_pgm2.CompileLinkValidate(shdr_files2);

            if (GL_FALSE == shdr_pgm2.IsLinked()) {
                std::cout << "Unable to compile/link/validate shader programs\n";
                std::cout << shdr_pgm2.GetLog() << "\n";
                std::exit(EXIT_FAILURE);
            }

            shdrpgms.insert(std::pair<std::string, GLSLShader>("Stencil", shdr_pgm2));
        }

        void CreateFramebuffer(unsigned int* framebuffer, unsigned int* texColorBuffer) {
            
            glGenFramebuffers(1, framebuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, *framebuffer);

            glGenTextures(1, texColorBuffer);
            glBindTexture(GL_TEXTURE_2D, *texColorBuffer);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Window::GetWidth(), Window::GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
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
    }
}