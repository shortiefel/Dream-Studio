/* Start Header**********************************************************************************/
/*
@file    Graphic.cpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    16/06/2021
\brief
This file has the function definition for Graphic

*/
/* End Header **********************************************************************************/

#include "Graphic/Graphic.hpp"
#include <iostream>
#include <fstream>

namespace GraphicImplementation {
    std::map<std::string, GLModel> models;
    std::map<std::string, GLSLShader> shdrpgms;

    void setup_vao_circle() {
        int const count{ 30 };

        std::vector<MathD::Vec2> pos_vtx(count);
        float const rad{ MathD::radians(360.f / static_cast<float>(count-2)) };

        pos_vtx[0] = MathD::Vec2(0.f, 0.f);

        for (int col{ 1 }; col < count; ++col) {
            pos_vtx[col] = MathD::Vec2(cos(rad * col), sin(rad * col));
        }

        std::vector<MathD::Vec3> clr_vtx(count);
        for (int col{ 0 }; col < count; ++col) {
            clr_vtx[col] = MathD::Vec3(
                0.f,
                1.f,
                0.f);
        }

        // Generate a VAO handle to encapsulate the VBO(s) and
        // state of this triangle mesh

        // transfer vertex position and color attributes to VBO
        GLuint vbo_hdl;
        glCreateBuffers(1, &vbo_hdl);

        glNamedBufferStorage(vbo_hdl,
            sizeof(MathD::Vec2) * pos_vtx.size(),
            nullptr, GL_DYNAMIC_STORAGE_BIT);
        glNamedBufferSubData(vbo_hdl, 0,
            sizeof(MathD::Vec2) * pos_vtx.size(), pos_vtx.data());
        glNamedBufferSubData(vbo_hdl, sizeof(MathD::Vec2) * pos_vtx.size(),
            sizeof(MathD::Vec3) * clr_vtx.size(), clr_vtx.data());

        // encapsulate information about contents of VBO and VBO handle
        // to another object called VAO
        GLuint vaoid;
        glCreateVertexArrays(1, &vaoid);
        glEnableVertexArrayAttrib(vaoid, 0);
        glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, 0, sizeof(MathD::Vec2));
        glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vaoid, 0, 0);

        glEnableVertexArrayAttrib(vaoid, 1);
        glVertexArrayVertexBuffer(vaoid, 1, vbo_hdl,
            sizeof(MathD::Vec2) * pos_vtx.size(), sizeof(MathD::Vec3));
        glVertexArrayAttribFormat(vaoid, 1, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vaoid, 1, 1);

        glBindVertexArray(0);

        // Step 4: Return appropriately initialized instance of GLApp::GLModel
        GLModel mdl;
        mdl.vaoid = vaoid;
        mdl.primitive_type = GL_TRIANGLE_FAN;
        mdl.draw_cnt = pos_vtx.size(); // number of vertices
        mdl.primitive_cnt = mdl.draw_cnt - 2; // number of primitives
        models.insert(std::pair<std::string, GLModel>("Circle", mdl));
    }
    void setup_vao_square() {
        std::array<MathD::Vec2, 4> pos_vtx{
             MathD::Vec2(1.f, -1.f), MathD::Vec2(1.f, 1.f),
             MathD::Vec2(-1.f, 1.f), MathD::Vec2(-1.f, -1.f)
        };
        std::array<MathD::Vec3, 4> clr_vtx{
            MathD::Vec3(1.f, 0.f, 0.f),
            MathD::Vec3(1.f, 0.f, 0.f),
            MathD::Vec3(1.f, 0.f, 0.f),
            MathD::Vec3(1.f, 0.f, 0.f)
        };

        GLuint vbo_hdl;
        glCreateBuffers(1, &vbo_hdl);

        glNamedBufferStorage(vbo_hdl,
            sizeof(MathD::Vec2) * pos_vtx.size() + sizeof(MathD::Vec3) * clr_vtx.size(),
            nullptr, GL_DYNAMIC_STORAGE_BIT);
        glNamedBufferSubData(vbo_hdl, 0,
            sizeof(MathD::Vec2) * pos_vtx.size(), pos_vtx.data());
        glNamedBufferSubData(vbo_hdl, sizeof(MathD::Vec2) * pos_vtx.size(),
            sizeof(MathD::Vec3) * clr_vtx.size(), clr_vtx.data());

        GLuint vaoid;
        glCreateVertexArrays(1, &vaoid);
        glEnableVertexArrayAttrib(vaoid, 0);
        glVertexArrayVertexBuffer(vaoid, 0, vbo_hdl, 0, sizeof(MathD::Vec2));
        glVertexArrayAttribFormat(vaoid, 0, 2, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vaoid, 0, 0);

        glEnableVertexArrayAttrib(vaoid, 1);
        glVertexArrayVertexBuffer(vaoid, 1, vbo_hdl,
            sizeof(MathD::Vec2) * pos_vtx.size(),
            sizeof(MathD::Vec3));
        glVertexArrayAttribFormat(vaoid, 1, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexArrayAttribBinding(vaoid, 1, 1);

        GLModel mdl;
        mdl.vaoid = vaoid;
        mdl.primitive_type = GL_TRIANGLE_FAN;
        //mdl.setup_shdrpgm(vtx_shdr, frg_shdr);
        mdl.draw_cnt = pos_vtx.size(); // number of vertices
        mdl.primitive_cnt = mdl.draw_cnt - 2; // number of primitives
        models.insert(std::pair<std::string, GLModel>("Square", mdl));
	}
    
    void setup_vao() {
        setup_vao_square();
        setup_vao_circle();
    }

    void setup_shdr() {
        std::cout << "shdr should be registered \n";
        std::vector<std::pair<GLenum, std::string>> shdr_files{
        std::make_pair(GL_VERTEX_SHADER, "shaders/OpenGLEngine.vert"),
        std::make_pair(GL_FRAGMENT_SHADER, "shaders/OpenGLEngine.frag")
        }; 

        GLSLShader shdr_pgm;
        shdr_pgm.CompileLinkValidate(shdr_files);

        if (GL_FALSE == shdr_pgm.IsLinked()) {
            std::cout << "Unable to compile/link/validate shader programs\n";
            std::cout << shdr_pgm.GetLog() << "\n";
            std::exit(EXIT_FAILURE);
        }
        shdrpgms.insert(std::pair<std::string, GLSLShader>("Default", shdr_pgm));   
    }

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