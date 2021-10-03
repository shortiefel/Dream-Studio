/* Start Header**********************************************************************************/
/*
@file    Graphic.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
         Chia Yi Da		chiayida98@gmail.com
@date    16/06/2021
\brief
This file has the functions declaration to be called by the graphic system


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "Engine/Header/Graphic/glslshader.hpp" // for GLSLShader
#include "Engine/Header/Graphic/GraphicOptions.hpp"
#include "Engine/Header/pch.hpp"
#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
    namespace GraphicImplementation {
        struct GLModel {
            GLenum primitive_type = GLenum{};
            GLuint primitive_cnt = GLuint{};
            GLuint vaoid = GLuint{}; // handle to VAO
            GLuint draw_cnt = GLuint{}; // how many elements of primitive of type
        };

        void CreateFramebuffer(GLsizei width, GLsizei height, unsigned int* framebuffer, unsigned int* texColorBuffer);

        //exist = false to remove framebuffer, to set buffer ignore exist
        void SetFramebuffer(unsigned int f, bool exist = true);
        void BindFramebuffer();
        void UnbindFramebuffer();

        // Install the shader program with object handle
        void UseShaderHandle(unsigned int prgm_handle);

        // De-install previously installed shader program object.
        void UnUseShaderHandle();

        extern std::map<GraphicShape, GLModel> models;
        extern std::map<GraphicShader, GLSLShader> shdrpgms;

        /*
        struct GLSprite {
            GLuint spriteWidth, spriteHeight;
            GLuint spritesheetWidth, spritesheetHeight;
            Math::vec2 position;
        };
        */
    }
}

#endif