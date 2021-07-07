/* Start Header**********************************************************************************/
/*
@file    Graphic.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/06/2021
\brief
This file has the function definition for Graphic


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Graphic/Graphic.hpp" 
#include <iostream>
#include <fstream>

namespace GraphicImplementation {
    std::map<std::string, GLModel> models;
    std::map<std::string, GLSLShader> shdrpgms;
    GLuint setup_texobj(std::string, GLuint, GLuint);

	void setup_vao_square() {
        // container contains vertices of Position, Color and Texture Coordinates respectively
        std::array<GLVertCont, 4> vtx = {
            MathD::Vec2(-1.f, -1.f), MathD::Vec3(1.f, 0.f, 0.f), MathD::Vec2(0.f, 0.f),
            MathD::Vec2(1.f, -1.f), MathD::Vec3(1.f, 0.f, 0.f), MathD::Vec2(1.f, 0.f),
            MathD::Vec2(1.f, 1.f), MathD::Vec3(1.f, 0.f, 0.f), MathD::Vec2(1.f, 1.f),
            MathD::Vec2(-1.f, 1.f), MathD::Vec3(1.f, 0.f, 0.f), MathD::Vec2(0.f, 1.f)
        };

        // VAO handle definition
        GLuint vbo_hdl;
        glCreateBuffers(1, &vbo_hdl);
        glNamedBufferStorage(vbo_hdl, sizeof(GLVertCont) * vtx.size(),
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

        std::array<GLVertCont, count> vtx;
        vtx[0] = { MathD::Vec2(0.f, 0.f), MathD::Vec3(0.f, 1.f, 0.f), MathD::Vec2(0.5f, 0.5f) };

        for (int col{ 1 }; col < count; ++col) {
            vtx[col] = { MathD::Vec2(cos(rad * col), sin(rad * col)), 
            MathD::Vec3(0.f, 1.f, 0.f), 
            MathD::Vec2(0.5f + cos(rad * col), 0.5f + sin(rad * col))};
        }

        // Generate a VAO handle to encapsulate the VBO(s) and
        // state of this triangle mesh

        // VAO handle definition
        GLuint vbo_hdl;
        glCreateBuffers(1, &vbo_hdl);
        glNamedBufferStorage(vbo_hdl, sizeof(GLVertCont) * vtx.size(),
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
    
    void setup_vao() {
        setup_vao_square();
        setup_vao_circle();
    }

    void setup_shdr() {
        std::vector<std::pair<GLenum, std::string>> shdr_files {
        std::make_pair(GL_VERTEX_SHADER, "shaders/OpenGLEngine.vert"),
        std::make_pair(GL_FRAGMENT_SHADER, "shaders/OpenGLEngine.frag")}; 

        GLSLShader shdr_pgm;
        shdr_pgm.CompileLinkValidate(shdr_files);

        if (GL_FALSE == shdr_pgm.IsLinked()) {
            std::cout << "Unable to compile/link/validate shader programs\n";
            std::cout << shdr_pgm.GetLog() << "\n";
            std::exit(EXIT_FAILURE);
        }

        shdrpgms.insert(std::pair<std::string, GLSLShader>("Default", shdr_pgm));   
    }


    /*
    $(SolutionDir)images will be the default location for all image files.
    Standardize image size to be 256 texels width and height with each texel 
    representing 32-bit RGBA value.
    */


    //void create_square_instance() {
    //    /*GLObject tem_obj;
    //    tem_obj.init();*/

    //    /*tem_obj.mdl_ref = models.find("Square");
    //    tem_obj.shd_ref = shdrpgms.find("Default");*/

    //    //objects.insert(std::pair<std::string, GLObject>("Square 1", tem_obj));
    //    std::cout << "third: " << shdrpgms.size() << "\n";
    //}

    //void GLObject::init() {
    //    //color = MathD::Vec3(0.f, 0.f, 0.f);
    //    // create a entity with transform
    //}
}