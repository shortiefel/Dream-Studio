/* Start Header**********************************************************************************/
/*
@file    Shader.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    16/06/2021
\brief
This file contains the definition of function that sets up all the shader files


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Graphic/Shader.hpp"
#include "Engine/Header/Graphic/Graphic.hpp" 

namespace Engine
{
    namespace GraphicImplementation 
    {
        void setup_shdr() 
        {
            // Default Shader for Objects
            std::vector<std::pair<GLSLShader::ShaderType, std::string>> shdr_files
            {
                std::make_pair(GLSLShader::ShaderType::VERTEX_SHADER, "Assets/Shaders/GraphicShader.vert"),
                std::make_pair(GLSLShader::ShaderType::FRAGMENT_SHADER, "Assets/Shaders/GraphicShader.frag") 
            };

            GLSLShader shdr_pgm;
            shdr_pgm.CompileLinkValidate(shdr_files);

            if (GL_FALSE == shdr_pgm.IsLinked()) 
            {
                std::cout << "Unable to compile/link/validate shader programs\n";
                std::cout << shdr_pgm.GetLog() << "\n";
                std::exit(EXIT_FAILURE);
            }

            shdrpgms.insert(std::pair<GraphicShader, GLSLShader>(GraphicShader::DEFAULT, shdr_pgm));



            // Debug Draw Shader for debugging 
            shdr_files = {
                std::make_pair(GLSLShader::ShaderType::VERTEX_SHADER, "Assets/Shaders/GraphicShader.vert"),
                std::make_pair(GLSLShader::ShaderType::FRAGMENT_SHADER, "Assets/Shaders/GraphicsDebugDraw.frag") 
            };

            GLSLShader shdr_pgm2;
            shdr_pgm2.CompileLinkValidate(shdr_files);

            if (GL_FALSE == shdr_pgm2.IsLinked()) 
            {
                std::cout << "Unable to compile/link/validate shader programs\n";
                std::cout << shdr_pgm2.GetLog() << "\n";
                std::exit(EXIT_FAILURE);
            }

            shdrpgms.insert(std::pair<GraphicShader, GLSLShader>(GraphicShader::DEBUG_DRAW, shdr_pgm2));
        }
    }
}