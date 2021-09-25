/* Start Header**********************************************************************************/
/*
@file    mesh.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    16/06/2021
\brief
This file contains the definition of function that sets up the vao of different meshes


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Graphic/mesh.hpp"
#include "Engine/Header/Graphic/Graphic.hpp"

namespace Engine {
    namespace GraphicImplementation {
        void setup_vao_square() {
            // container contains vertices of Position, Color and Texture Coordinates respectively
            std::array<GLMesh, 4> vtx = {
                Math::vec2(-1.f, -1.f), Math::vec3(1.f, 0.f, 0.f), Math::vec2(0.f, 0.f),
                Math::vec2(1.f, -1.f), Math::vec3(1.f, 0.f, 0.f), Math::vec2(1.f, 0.f),
                Math::vec2(1.f, 1.f), Math::vec3(1.f, 0.f, 0.f), Math::vec2(1.f, 1.f),
                Math::vec2(-1.f, 1.f), Math::vec3(1.f, 0.f, 0.f), Math::vec2(0.f, 1.f)
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
            glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, 0, 2 * sizeof(Math::vec2) + sizeof(Math::vec3));
            glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 0, 0);

            // Color vertex
            glEnableVertexArrayAttrib(vaoid, 1);
            glVertexArrayVertexBuffer(vaoid, 1, vbo_hdl, sizeof(Math::vec2),
                2 * sizeof(Math::vec2) + sizeof(Math::vec3));
            glVertexArrayAttribFormat(vaoid, 1, 3, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 1, 1);

            // Texture vertex
            glEnableVertexArrayAttrib(vaoid, 2);
            glVertexArrayVertexBuffer(vaoid, 2, vbo_hdl, sizeof(Math::vec2) + sizeof(Math::vec3),
                2 * sizeof(Math::vec2) + sizeof(Math::vec3));
            glVertexArrayAttribFormat(vaoid, 2, 2, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 2, 2);

            glBindVertexArray(0);

            GLModel mdl;
            mdl.vaoid = vaoid;
            //mdl.setup_shdrpgm(vtx_shdr, frg_shdr);
            mdl.primitive_type = GL_TRIANGLE_FAN;
            mdl.draw_cnt = 4; // number of vertices
            mdl.primitive_cnt = 2; // number of primitives
            models.insert(std::pair<GraphicShape, GLModel>(GraphicShape::SQUARE, mdl));
        }

        void setup_vao_circle() {
            // Number of vertices
            int const count{ 52 };
            float rad = Math::radians(360.f / static_cast<float>(count - 2));

            std::array<GLMesh, count> vtx;
            vtx[0] = { Math::vec2(0.f, 0.f), Math::vec3(0.f, 1.f, 0.f), Math::vec2(0.5f, 0.5f) };

            for (int col{ 1 }; col < count; ++col) {
                vtx[col] = { Math::vec2(cos(rad * col), sin(rad * col)),
                Math::vec3(0.f, 1.f, 0.f),
                Math::vec2(0.5f + cos(rad * col), 0.5f + sin(rad * col)) };
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
            glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, 0, 2 * sizeof(Math::vec2) + sizeof(Math::vec3));
            glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 0, 0);

            // Colour vertex
            glEnableVertexArrayAttrib(vaoid, 1);
            glVertexArrayVertexBuffer(vaoid, 1, vbo_hdl, sizeof(Math::vec2),
                2 * sizeof(Math::vec2) + sizeof(Math::vec3));
            glVertexArrayAttribFormat(vaoid, 1, 3, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 1, 1);

            // Texture vertex
            glEnableVertexArrayAttrib(vaoid, 2);
            glVertexArrayVertexBuffer(vaoid, 2, vbo_hdl, sizeof(Math::vec2) + sizeof(Math::vec3),
                2 * sizeof(Math::vec2) + sizeof(Math::vec3));
            glVertexArrayAttribFormat(vaoid, 2, 2, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 2, 2);

            glBindVertexArray(0);

            // Step 4: Return appropriately initialized instance of GLApp::GLModel
            GLModel mdl;
            mdl.vaoid = vaoid;
            mdl.primitive_type = GL_TRIANGLE_FAN;
            mdl.draw_cnt = static_cast<GLuint>(count); // number of vertices
            mdl.primitive_cnt = mdl.draw_cnt - 2; // number of primitives
            models.insert(std::pair<GraphicShape, GLModel>(GraphicShape::CIRCLE, mdl));
        }

        void setup_vao_stencilBox() {
            int slices = 1, stacks = 1;

            // vertices positions
            int const count{ 2 * (slices + 1) + 2 * (stacks + 1) };
            std::vector<Math::vec2> pos_vtx(count);

            float const u{ 2.f / static_cast<float>(slices) };
            float const v{ 2.f / static_cast<float>(stacks) };

            int index = 0;

            for (int col{ 0 }; col <= slices; ++col) {
                float x{ u * static_cast<float> (col) - 1.f };
                pos_vtx[index++] = Math::vec2(x, -1.f);
                pos_vtx[index++] = Math::vec2(x, 1.f);
            }

            for (int row{ 0 }; row <= stacks; ++row) {
                float y{ v * static_cast<float> (row) - 1.f };
                pos_vtx[index++] = Math::vec2(-1.f, y);
                pos_vtx[index++] = Math::vec2(1.f, y);
            }

            // Color
            std::vector<Math::vec3> clr_vtx(pos_vtx.size());
            for (int i{ 0 }; i < pos_vtx.size(); ++i) {
                clr_vtx[i] = Math::vec3(1.f, 0.f, 0.f);
            }


            //VAO handle definition
            GLuint vbo_hdl;
            glCreateBuffers(1, &vbo_hdl);
            glNamedBufferStorage(vbo_hdl, sizeof(Math::vec2) * pos_vtx.size() +
                sizeof(Math::vec3) * clr_vtx.size(),
                nullptr, GL_DYNAMIC_STORAGE_BIT);

            //pos_vtx
            glNamedBufferSubData(vbo_hdl, 0,
                sizeof(Math::vec2) * pos_vtx.size(), pos_vtx.data());
            //clr_vtx
            glNamedBufferSubData(vbo_hdl, sizeof(Math::vec2) * pos_vtx.size(),
                sizeof(Math::vec3) * clr_vtx.size(), clr_vtx.data());

            GLuint vaoid;
            glCreateVertexArrays(1, &vaoid);

            //pos_vtx
            glEnableVertexArrayAttrib(vaoid, 0);
            glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, 0, sizeof(Math::vec2));
            glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 0, 0);
            //clr_vtx
            glEnableVertexArrayAttrib(vaoid, 1);
            glVertexArrayVertexBuffer(vaoid, 1, vbo_hdl,
                sizeof(Math::vec2) * pos_vtx.size(), sizeof(Math::vec3));
            glVertexArrayAttribFormat(vaoid, 1, 3, GL_FLOAT, GL_FALSE, 0);
            glVertexArrayAttribBinding(vaoid, 1, 1);
            glBindVertexArray(0);

            GLModel mdl;
            mdl.vaoid = vaoid;
            mdl.primitive_type = GL_LINES;
            mdl.draw_cnt = static_cast<GLuint>(pos_vtx.size()); // number of vertices
            mdl.primitive_cnt = mdl.draw_cnt / 2; // number of primitives
            models.insert(std::pair<GraphicShape, GLModel>(GraphicShape::STENCIL, mdl));
        }

        void setup_vao() {
            setup_vao_stencilBox();
            setup_vao_square();
            setup_vao_circle();
        }
    }
}