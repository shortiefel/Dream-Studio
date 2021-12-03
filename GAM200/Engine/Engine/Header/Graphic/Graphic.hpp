/* Start Header**********************************************************************************/
/*
@file    Graphic.hpp
@author  Chia Yi Da		c.yida@digipen.edu      100%
@date    16/06/2021
\brief
This file contains functions declaration that is to be called by the Graphic System


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "Engine/Header/Graphic/GLSLShader.hpp"
#include "Engine/Header/Graphic/GraphicOptions.hpp"
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/ECS/System/CameraSystem.hpp"

#include "Engine/Header/pch.hpp"

namespace Engine
{
    namespace GraphicImplementation
    {
        // Install the shader program with object handle
        void UseShaderHandle(unsigned int prgm_handle);

        // De-install previously installed shader program object.
        void UnUseShaderHandle();

        // Fades scene when called; user is able to choose colour and fading time
        // Default fade in to black
        bool FadeScene(float time, float _dt, 
            Math::mat3 _camMatrix = CameraSystem::GetInstance().GetTransform(),
            Math::vec4 _colourBegin = {0.0f, 0.0f, 0.0f, 0.0f}, Math::vec4 _colourEnd = { 0.0f, 0.0f, 0.0f, 1.0f });


        extern std::map<GraphicShader, GLSLShader> shdrpgms;
    }
}

#endif


// Code that might be used for the future


// void CreateFramebuffer(GLsizei width, GLsizei height, unsigned int* framebuffer, unsigned int* texColorBuffer);

// exist = false to remove framebuffer, to set buffer ignore exist
/*
void SetFramebuffer(unsigned int f, bool exist = true);
void BindFramebuffer();
void UnbindFramebuffer();
*/