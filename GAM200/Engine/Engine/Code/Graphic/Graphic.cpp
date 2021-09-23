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

        void setup_vao_square() {
            // container contains vertices of Position, Color and Texture Coordinates respectively
            std::array<GLMesh, 4> vtx = {
                MathD::Vec2(-1.f, -1.f), MathD::Vec3(1.f, 0.f, 0.f), MathD::Vec2(0.f, 0.f),
                MathD::Vec2(1.f, -1.f), MathD::Vec3(1.f, 0.f, 0.f), MathD::Vec2(1.f, 0.f),
                MathD::Vec2(1.f, 1.f), MathD::Vec3(1.f, 0.f, 0.f), MathD::Vec2(1.f, 1.f),
                MathD::Vec2(-1.f, 1.f), MathD::Vec3(1.f, 0.f, 0.f), MathD::Vec2(0.f, 1.f)
            };

            // VAO handle definition
            GLuint vbo_hdl;
            glCreateBuffers(1, &vbo_hdl);
            glNamedBufferStorage(vbo_hdl, sizeof(GLMesh) * vtx.size(),
                vtx.data(), GL_DYNAMIC_STORAGE_BIT);

            GLuint vaoid;
            glCreateVertexArrays(1, &vaoid);

            // Square vertex
            glEnableVertexArrayAttrib(vaoid, 0);
            glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, 0, 2 * sizeof(MathD::Vec2) + sizeof(MathD::Vec3));
            glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 0, 0);

            // Color vertex
            glEnableVertexArrayAttrib(vaoid, 1);
            glVertexArrayVertexBuffer(vaoid, 1, vbo_hdl, sizeof(MathD::Vec2),
                2 * sizeof(MathD::Vec2) + sizeof(MathD::Vec3));
            glVertexArrayAttribFormat(vaoid, 1, 3, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 1, 1);

            // Texture vertex
            glEnableVertexArrayAttrib(vaoid, 2);
            glVertexArrayVertexBuffer(vaoid, 2, vbo_hdl, sizeof(MathD::Vec2) + sizeof(MathD::Vec3),
                2 * sizeof(MathD::Vec2) + sizeof(MathD::Vec3));
            glVertexArrayAttribFormat(vaoid, 2, 2, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 2, 2);

            glBindVertexArray(0);

            GLModel mdl;
            mdl.vaoid = vaoid;
            //mdl.setup_shdrpgm(vtx_shdr, frg_shdr);
            mdl.primitive_type = GL_TRIANGLE_FAN;
            mdl.draw_cnt = 4; // number of vertices
            mdl.primitive_cnt = 2; // number of primitives
            models.insert(std::pair<std::string, GLModel>("Square", mdl));
        }

        void setup_vao_circle() {
            // Number of vertices
            int const count{ 52 };
            float rad = MathD::radians(360.f / static_cast<float>(count - 2));

            std::array<GLMesh, count> vtx;
            vtx[0] = { MathD::Vec2(0.f, 0.f), MathD::Vec3(0.f, 1.f, 0.f), MathD::Vec2(0.5f, 0.5f) };

            for (int col{ 1 }; col < count; ++col) {
                vtx[col] = { MathD::Vec2(cos(rad * col), sin(rad * col)),
                MathD::Vec3(0.f, 1.f, 0.f),
                MathD::Vec2(0.5f + cos(rad * col), 0.5f + sin(rad * col)) };
            }

            // Generate a VAO handle to encapsulate the VBO(s) and
            // state of this triangle mesh

            // VAO handle definition
            GLuint vbo_hdl;
            glCreateBuffers(1, &vbo_hdl);
            glNamedBufferStorage(vbo_hdl, sizeof(GLMesh) * vtx.size(),
                vtx.data(), GL_DYNAMIC_STORAGE_BIT);

            GLuint vaoid;
            glCreateVertexArrays(1, &vaoid);

            // Position vertex
            glEnableVertexArrayAttrib(vaoid, 0);
            glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, 0, 2 * sizeof(MathD::Vec2) + sizeof(MathD::Vec3));
            glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 0, 0);

            // Colour vertex
            glEnableVertexArrayAttrib(vaoid, 1);
            glVertexArrayVertexBuffer(vaoid, 1, vbo_hdl, sizeof(MathD::Vec2),
                2 * sizeof(MathD::Vec2) + sizeof(MathD::Vec3));
            glVertexArrayAttribFormat(vaoid, 1, 3, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 1, 1);

            // Texture vertex
            glEnableVertexArrayAttrib(vaoid, 2);
            glVertexArrayVertexBuffer(vaoid, 2, vbo_hdl, sizeof(MathD::Vec2) + sizeof(MathD::Vec3),
                2 * sizeof(MathD::Vec2) + sizeof(MathD::Vec3));
            glVertexArrayAttribFormat(vaoid, 2, 2, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 2, 2);

            glBindVertexArray(0);

            // Step 4: Return appropriately initialized instance of GLApp::GLModel
            GLModel mdl;
            mdl.vaoid = vaoid;
            mdl.primitive_type = GL_TRIANGLE_FAN;
            mdl.draw_cnt = static_cast<GLuint>(count); // number of vertices
            mdl.primitive_cnt = mdl.draw_cnt - 2; // number of primitives
            models.insert(std::pair<std::string, GLModel>("Circle", mdl));
        }

        void setup_vao_stencilBox() {
            int slices = 1, stacks = 1;

            // vertices positions
            int const count{ 2 * (slices + 1) + 2 * (stacks + 1) };
            std::vector<MathD::Vec2> pos_vtx(count);

            float const u{ 2.f / static_cast<float>(slices) };
            float const v{ 2.f / static_cast<float>(stacks) };

            int index = 0;

            for (int col{ 0 }; col <= slices; ++col) {
                float x{ u * static_cast<float> (col) - 1.f };
                pos_vtx[index++] = MathD::Vec2(x, -1.f);
                pos_vtx[index++] = MathD::Vec2(x, 1.f);
            }

            for (int row{ 0 }; row <= stacks; ++row) {
                float y{ v * static_cast<float> (row) - 1.f };
                pos_vtx[index++] = MathD::Vec2(-1.f, y);
                pos_vtx[index++] = MathD::Vec2(1.f, y);
            }

            // Color
            std::vector<MathD::Vec3> clr_vtx(pos_vtx.size());
            for (int i{ 0 }; i < pos_vtx.size(); ++i) {
                clr_vtx[i] = MathD::Vec3(1.f, 0.f, 0.f);
            }


            //VAO handle definition
            GLuint vbo_hdl;
            glCreateBuffers(1, &vbo_hdl);
            glNamedBufferStorage(vbo_hdl, sizeof(MathD::Vec2) * pos_vtx.size() +
                sizeof(MathD::Vec3) * clr_vtx.size(),
                nullptr, GL_DYNAMIC_STORAGE_BIT);

            //pos_vtx
            glNamedBufferSubData(vbo_hdl, 0,
                sizeof(MathD::Vec2) * pos_vtx.size(), pos_vtx.data());
            //clr_vtx
            glNamedBufferSubData(vbo_hdl, sizeof(MathD::Vec2) * pos_vtx.size(),
                sizeof(MathD::Vec3) * clr_vtx.size(), clr_vtx.data());

            GLuint vaoid;
            glCreateVertexArrays(1, &vaoid);

            //pos_vtx
            glEnableVertexArrayAttrib(vaoid, 0);
            glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, 0, sizeof(MathD::Vec2));
            glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 0, 0);
            //clr_vtx
            glEnableVertexArrayAttrib(vaoid, 1);
            glVertexArrayVertexBuffer(vaoid, 1, vbo_hdl,
                sizeof(MathD::Vec2) * pos_vtx.size(), sizeof(MathD::Vec3));
            glVertexArrayAttribFormat(vaoid, 1, 3, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 1, 1);
            glBindVertexArray(0);

            GLModel mdl;
            mdl.vaoid = vaoid;
            mdl.primitive_type = GL_LINES;
            mdl.draw_cnt = static_cast<GLuint>(pos_vtx.size()); // number of vertices
            mdl.primitive_cnt = mdl.draw_cnt / 2; // number of primitives
            models.insert(std::pair<std::string, GLModel>("stencilBox", mdl));
        }

        void setup_vao() {
            setup_vao_stencilBox();
            setup_vao_square();
            setup_vao_circle();
        }

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