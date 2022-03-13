/* Start Header**********************************************************************************/
/*
@file    Shader.cpp
@author  Chia Yi Da		c.yida@digipen.edu  	100%
@date    16/06/2021
\brief
This file contains function definition for shaders that sets up shader files


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
        // Function that sets up all shader files
        void setup_shdr()
        {
            // Default Shader for Game objects
            std::vector<std::pair<GLSLShader::ShaderType, std::string>> shdr_files
            {
                std::make_pair(GLSLShader::ShaderType::Vertex_Shader, "Assets/Shaders/Default.vert"),
                std::make_pair(GLSLShader::ShaderType::Fragment_Shader, "Assets/Shaders/Default.frag")
            };

            GLSLShader shdr_pgm;
            shdr_pgm.CompileLinkValidate(shdr_files);

            if (GL_FALSE == shdr_pgm.IsLinked())
            {
                std::cout << "Unable to compile/link/validate shader programs\n";
                std::cout << shdr_pgm.GetLog() << "\n";
                std::exit(EXIT_FAILURE);
            }

            shdrpgms.insert(std::pair<GraphicShader, GLSLShader>(GraphicShader::Default, shdr_pgm));



            // Shader for Collision Rendering
            shdr_files = {
                std::make_pair(GLSLShader::ShaderType::Vertex_Shader, "Assets/Shaders/Lines.vert"),
                std::make_pair(GLSLShader::ShaderType::Fragment_Shader, "Assets/Shaders/Lines.frag")
            };

            GLSLShader shdr_pgm2;
            shdr_pgm2.CompileLinkValidate(shdr_files);

            if (GL_FALSE == shdr_pgm2.IsLinked())
            {
                std::cout << "Unable to compile/link/validate shader programs\n";
                std::cout << shdr_pgm2.GetLog() << "\n";
                std::exit(EXIT_FAILURE);
            }

            shdrpgms.insert(std::pair<GraphicShader, GLSLShader>(GraphicShader::Collision, shdr_pgm2));



            // Shader for Font Rendering
            shdr_files = {
                std::make_pair(GLSLShader::ShaderType::Vertex_Shader, "Assets/Shaders/Font.vert"),
                std::make_pair(GLSLShader::ShaderType::Fragment_Shader, "Assets/Shaders/Font.frag")
            };

            GLSLShader shdr_pgm3;
            shdr_pgm3.CompileLinkValidate(shdr_files);

            if (GL_FALSE == shdr_pgm3.IsLinked())
            {
                std::cout << "Unable to compile/link/validate shader programs\n";
                std::cout << shdr_pgm3.GetLog() << "\n";
                std::exit(EXIT_FAILURE);
            }

            shdrpgms.insert(std::pair<GraphicShader, GLSLShader>(GraphicShader::Font_Draw, shdr_pgm3));



            // Shader for Shadow Mapping
            shdr_files = {
                std::make_pair(GLSLShader::ShaderType::Vertex_Shader, "Assets/Shaders/SimpleDepth.vert"),
                std::make_pair(GLSLShader::ShaderType::Fragment_Shader, "Assets/Shaders/SimpleDepth.frag")
            };

            GLSLShader shdr_pgm4;
            shdr_pgm4.CompileLinkValidate(shdr_files);

            if (GL_FALSE == shdr_pgm4.IsLinked())
            {
                std::cout << "Unable to compile/link/validate shader programs\n";
                std::cout << shdr_pgm4.GetLog() << "\n";
                std::exit(EXIT_FAILURE);
            }

            shdrpgms.insert(std::pair<GraphicShader, GLSLShader>(GraphicShader::Simple_Depth, shdr_pgm4));

            /*

            // Shader for Light
            shdr_files = {
                std::make_pair(GLSLShader::ShaderType::Vertex_Shader, "Assets/Shaders/Light.vert"),
                std::make_pair(GLSLShader::ShaderType::Fragment_Shader, "Assets/Shaders/Light.frag")
            };

            GLSLShader shdr_pgm5;
            shdr_pgm5.CompileLinkValidate(shdr_files);

            if (GL_FALSE == shdr_pgm5.IsLinked())
            {
                std::cout << "Unable to compile/link/validate shader programs\n";
                std::cout << shdr_pgm5.GetLog() << "\n";
                std::exit(EXIT_FAILURE);
            }

            shdrpgms.insert(std::pair<GraphicShader, GLSLShader>(GraphicShader::Light, shdr_pgm5));

            */
        }
    }
}