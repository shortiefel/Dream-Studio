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
#include "Engine/Header/Management/GameState.hpp"

namespace Engine
{
    namespace GraphicImplementation
    {
        // Struct declaration
        struct FadeStruct
        {
            float lifeTime = 0.0f;
            float lifeRemaining = 0.0f;

            Math::vec4 colourBegin;
            Math::vec4 colourEnd;

            bool flagFade = false;
        };

        static FadeStruct fadeStruct;

        std::map<GraphicShader, GLSLShader> shdrpgms;

        void UseShaderHandle(unsigned int prgm_handle)
        {
            glUseProgram(prgm_handle);
        }

        void UnUseShaderHandle()
        {
            glUseProgram(0);
        }

        bool FadeScene(float time, float _dt, Math::mat3 _camMatrix, Math::vec4 _colourBegin, Math::vec4 _colourEnd)
        {
            // Enable GL_BLEND for transparency of textures
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            GraphicImplementation::Renderer::BeginQuadBatch();

            // Load default shader program
            const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::Default].GetHandle();
            UseShaderHandle(shd_ref_handle);

            // Set uniform
            GLSLShader::SetUniform("uCamMatrix", _camMatrix, shd_ref_handle);

            if (fadeStruct.flagFade == false)
            {
                fadeStruct.lifeTime = fadeStruct.lifeRemaining = time;
                fadeStruct.colourBegin = _colourBegin;
                fadeStruct.colourEnd = _colourEnd;

                fadeStruct.flagFade = true;
            }
            
            if (fadeStruct.flagFade == true)
            {

                fadeStruct.lifeRemaining -= _dt;

                float life = fadeStruct.lifeRemaining / fadeStruct.lifeTime;
                Math::vec4 colour = Math::Lerp(fadeStruct.colourEnd, fadeStruct.colourBegin, life);

                GraphicImplementation::Renderer::DrawQuad({ 0.0f, 0.0f }, { 200.0f, 200.0f }, 0.0f, colour, 0.0f);

                if (fadeStruct.lifeRemaining <= 0.0f) fadeStruct.flagFade = false;
            }

            Renderer::EndQuadBatch();
            Renderer::FlushQuad();

            // Unload shader program
            UnUseShaderHandle();

            glDisable(GL_BLEND);

            return fadeStruct.flagFade;
        }
    }
}