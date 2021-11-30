/* Start Header**********************************************************************************/
/*
@file    Graphic.cpp
@author  Chia Yi Da		c.yida@digipen.edu  	100%
@date    16/06/2021
\brief
This file has the function definition for Graphic


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Graphic/Graphic.hpp" 

#include "Engine/Header/Graphic/Mesh.hpp"
#include "Engine/Header/Time/DeltaTime.hpp"

namespace Engine
{
    namespace GraphicImplementation
    {
        std::map<GraphicShader, GLSLShader> shdrpgms;

        void UseShaderHandle(unsigned int prgm_handle)
        {
            glUseProgram(prgm_handle);
        }

        void UnUseShaderHandle()
        {
            glUseProgram(0);
        }


        void FadeInScene(Math::vec3 _colour, float time, float _dt)
        {
            if (fadeStruct.flag == false)
            {
                fadeStruct.lifeTime = fadeStruct.lifeRemaining = time;
                fadeStruct.colourBegin = { _colour.x, _colour.y, _colour.z, 0.0f };
                fadeStruct.colourEnd = { _colour.x, _colour.y, _colour.z, 1.0f };

                fadeStruct.flag = true;
            }
            else if (fadeStruct.flag == true)
            {
                fadeStruct.lifeRemaining -= _dt;

                float life = fadeStruct.lifeRemaining / fadeStruct.lifeTime;
                Math::vec4 colour = Math::Lerp(fadeStruct.colourEnd, fadeStruct.colourBegin, life);

                if (fadeStruct.lifeRemaining <= 0.0f) fadeStruct.flag = false;

                if (fadeStruct.flag == true) 
                    GraphicImplementation::Renderer::DrawQuad({0.0f, 0.0f}, { 2.0f, 2.0f }, 0.0f, colour);
            }
        }

        void FadeOutScene(Math::vec4 _colour, float time, float _dt)
        {
            if (fadeStruct.flag == false)
            {
                fadeStruct.lifeTime = fadeStruct.lifeRemaining = time;
                fadeStruct.colourBegin = { _colour.x, _colour.y, _colour.z, 1.0f };
                fadeStruct.colourEnd = { _colour.x, _colour.y, _colour.z, 0.0f };

                fadeStruct.flag = true;
            }
            else if (fadeStruct.flag == true)
            {
                fadeStruct.lifeRemaining -= _dt;

                float life = fadeStruct.lifeRemaining / fadeStruct.lifeTime;
                Math::vec4 colour = Math::Lerp(fadeStruct.colourEnd, fadeStruct.colourBegin, life);

                if (fadeStruct.lifeRemaining <= 0.0f) fadeStruct.flag = false;

                if (fadeStruct.flag == true)
                    GraphicImplementation::Renderer::DrawQuad({ 0.0f, 0.0f }, { 2.0f, 2.0f }, 0.0f, colour);
            }
        }
    }
}

// Code that might be used for the future

/*
// Frame buffer index
unsigned int fbo;
bool fbo_exist = false;

void CreateFramebuffer(GLsizei width, GLsizei height, unsigned int* framebuffer, unsigned int* texColorBuffer)
{
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
    {
        LOG_ERROR("Error: Framebuffer is not complete");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DeleteFramebuffer(unsigned int f)
{
    glDeleteFramebuffers(1, &f);
}

void SetFramebuffer(unsigned int f, bool exist)
{
    if (!exist) {
        fbo_exist = false;
        return;
    }

    fbo_exist = true;
    fbo = f;
}

void BindFramebuffer()
{
    if (fbo_exist)
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void UnbindFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
*/