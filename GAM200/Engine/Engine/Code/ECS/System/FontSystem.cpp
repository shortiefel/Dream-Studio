/* Start Header**********************************************************************************/
/*!
@file FontSystem.cpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
@date 29/06/2021
\brief

This file contain the font system.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Logging.hpp"
#include "Engine/Header/ECS/System/FontSystem.hpp"

#include "Engine/Header/ECS/DreamECS.hpp"
#include "Engine/Header/ECS/Component/ComponentArray.hpp"
#include "Engine/Header/ECS/Component/Graphics/TransformComponent.hpp"
#include "Engine/Header/ECS/Component/Graphics/TextureComponent.hpp"
#include "Engine/Header/ECS/Component/UI/TextComponent.hpp"
#include "Engine/Header/ECS/Component/Physics/ColliderComponent.hpp"

#include "Engine/Header/Graphic/Mesh.hpp"
#include "Engine/Header/Graphic/Shader.hpp"
#include "Engine/Header/Graphic/GLSLShader.hpp"

#include <GL/glew.h>
#include <ft2build.h>
#include <iostream>

#ifdef _WIN32
#pragma comment(lib, "freetype.lib")
#endif

#include "Engine/Header/Application.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include FT_FREETYPE_H

namespace Engine
{
    void FontSystem::Render(Math::mat3 camMatrix, Graphic::FrameBuffer* _fbo) 
    {
        GLboolean fontDraw;
        if (!_fbo)
            fontDraw = GL_TRUE;
        else
            fontDraw = GL_FALSE;

        //GraphicImplementation::BindFramebuffer();
        if (fontDraw)
            GraphicSystem::GetInstance().GetFrameBuffer().Bind();
        else
            _fbo->Bind();

        // Load shader program
        const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::FONT_DRAW].GetHandle();
        GraphicImplementation::UseShaderHandle(shd_ref_handle);

        GraphicImplementation::Renderer::ResetStats();
        GraphicImplementation::Renderer::BeginBatch(!fontDraw);

        const auto& textArray = DreamECS::GetInstance().GetComponentArrayData<TextComponent>();
        for (const auto& text : textArray) {
            const Entity_id& entity_id = text.GetEntityId();
            if (EntityId_Check(entity_id)) break;
            if (!text.isActive) continue;

            TransformComponent* transform = DreamECS::GetInstance().GetComponentPTR<TransformComponent>(entity_id);
            if (!transform || !transform->isActive) continue;

            GraphicImplementation::Renderer::DrawQuad(transform->position, transform->scale, transform->angle, text.texobj_hdl);
            //font renderer
            RenderText("Hello World!", 100.0f, 10.0f, 50.0f, glm::vec3(0.0f,0.8f,1.0f));
            // 
            // to draw debug lines
            //if (fontDraw == GL_TRUE) {
            //    ColliderComponent* collider = DreamECS::GetInstance().GetComponentPTR<ColliderComponent>(entity_id);

            //    // when object has collider, get collider matrix
            //    if (collider != nullptr)
            //    {
            //        if (text.mdl_ref == GraphicShape::SQUARE)
            //        {
            //            GraphicImplementation::Renderer::DrawQuadDebug(collider->offset_position + transform->position,
            //                collider->offset_scale * transform->scale,
            //                transform->angle);
            //        }
            //        else if (text.mdl_ref == GraphicShape::CIRCLE)
            //        {
            //            GraphicImplementation::Renderer::DrawCircleDebug(collider->offset_position + transform->position,
            //                collider->offset_scale * transform->scale,
            //                transform->angle);
            //        }
            //    }
            //}
        }


        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //GLSLShader::SetUniform("uCamMatrix", Math::mat3{}, shd_ref_handle);
        GLSLShader::SetUniform("projection", camMatrix, shd_ref_handle);

        GraphicImplementation::Renderer::EndBatch(!fontDraw);
        GraphicImplementation::Renderer::Flush(!fontDraw);

        // unload shader program
        GraphicImplementation::UnUseShaderHandle();

        if (fontDraw)
            GraphicSystem::GetInstance().GetFrameBuffer().Unbind();
        else
            _fbo->Unbind();
    }

    bool FontSystem::Create() {
        LOG_INSTANCE("Font System created");
        return true;
    }

    void FontSystem::Destroy() {
        LOG_INSTANCE("Font System destroyed");
    }

    void FontSystem::RenderText(std::string text, float x, float y, float scale, const glm::vec3& colour)
    {
        // Activate corresponding render state	
        glBindVertexArray(vao);
        //shader.Use();
        glUniform3f(glGetUniformLocation(shader.id, "textColor"), colour.x, colour.y, colour.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(vao);

        //std::unordered_map<GLchar, Character> map = MyResourceManager.GetFontCharacterMap()[_characterMapId];


            //Iterate through all characters
        for (auto iter = text.begin(); iter != text.end(); iter++)
        {
            Character ch = characters[*iter];

            //x position
            GLfloat xpos = x + ch.bearing.x * scale;

            //y position
            GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

            //width
            GLfloat width = ch.size.x * scale;

            //height 
            GLfloat height = ch.size.y * scale;

            //update VBO for each character based on real-time
            GLfloat vertices[6][4] =
            {
                //position( , ) , text_coordinate( , )
                {xpos, (ypos + height) , 0.0, 0.0},
                {xpos, ypos, 0.0, 1.0},
                {(xpos + width), ypos, 1.0, 1.0},
                {xpos, (ypos + height), 0.0, 0.0},
                {xpos + width, ypos, 1.0, 1.0},
                {xpos + width, ypos + height, 1.0, 0.0}
            };
            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.texture_ID);
            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
            x += (ch.advance >> 6) * scale;
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    //bool FontSystem::Load(std::string path)
    //{
    //    std::string temp = "DefaultFont";
    //    glEnable(GL_CULL_FACE);
    //    glEnable(GL_BLEND);
    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //    glm::mat4 projection = glm::ortho(-640.0f, 640.0f, -512.0f, 512.0f, -150.0f, 150.0f);

    //    shader.Select();
    //    //Freetype Settings
    //    FT_Library ft;
    //    if (FT_Init_FreeType(&ft))
    //    {
    //        std::cerr << "ERROR::FREETYPE: Could not init FreeType Lib\n";
    //        return false;
    //    }
    //    FT_Face face;
    //    if (FT_New_Face(ft, "Assets/Fonts/arial.ttf", 0, &face))
    //    {
    //        std::cerr << "ERROR::FREETYPE: Failed to load font.\n";
    //        return false;
    //    }

    //    FT_Set_Pixel_Sizes(face, 0, 48);

    //    //disable byte-alignment restriction
    //    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //    //storing ASCII 128 characters
    //    for (GLubyte ch = 0; ch < 128; ch++)
    //    {
    //        // Load chracter glyph
    //        if (FT_Load_Char(face, ch, FT_LOAD_RENDER))
    //        {
    //            std::cerr << "ERROR::FREETYPE: Failed to load "
    //                << ch << "Glyph.\n";
    //            continue;
    //        }

    //        //To generate texture
    //        GLuint texture;

    //        glGenTextures(1, &texture);
    //        glBindTexture(GL_TEXTURE_2D, texture);
    //        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

    //        // Set texture options
    //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //        Character character =
    //        {
    //            texture,
    //            glm::ivec2(face->glyph->bitmap.width, GL_CLAMP_TO_EDGE),
    //            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
    //            face->glyph->advance.x

    //        };

    //        characters.insert(std::pair<char, Character>(ch, character));

    //        //Destroy Freetype once
    //        FT_Done_Face(face);
    //        FT_Done_FreeType(ft);

    //        //Configure VAO/VBO for texture quads
    //        glGenVertexArrays(1, &vao);
    //        glGenBuffers(1, &vbo);
    //        glBindVertexArray(vao);
    //        glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW); // 2D quad requires 6 vertices of 4 float each
    //        glEnableVertexAttribArray(0);
    //        glVertexAttribPointer(0, 4 /*pos, texCoord*/, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    //        glBindBuffer(GL_ARRAY_BUFFER, 0);
    //        glBindVertexArray(0);

    //        glBindVertexArray(NULL);
    //        glBindBuffer(GL_ARRAY_BUFFER, NULL);
    //        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);

    //        glDisable(GL_CULL_FACE);
    //    }
    //}


//    void FontSystem::RenderText(GLSLShader &shader, std::string text, float x, float y, float scale, const glm::ivec3& colour, float rotation)
//{
//    //Backup state to add in more for texture
//    GLenum last_active_texture;
//    glGetIntegerv(GL_ACTIVE_TEXTURE, (GLint*)&last_active_texture);
//    glActiveTexture(GL_TEXTURE0);
//    GLint last_program;
//    glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
//    GLint last_texture;
//    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
//    GLint last_sampler;
//    glGetIntegerv(GL_SAMPLER_BINDING, &last_sampler);
//    GLint last_array_buffer;
//    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &last_array_buffer);
//    GLint last_element_array_buffer;
//    glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer);
//    GLint last_vertex_array;
//    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &last_vertex_array);
//    GLint last_polygon_mode[2];
//    glGetIntegerv(GL_POLYGON_MODE, last_polygon_mode);
//    GLint last_viewport[4];
//    glGetIntegerv(GL_VIEWPORT, last_viewport);
//    GLint last_scissor_box[4];
//    glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);
//    GLenum last_blend_src_rgb;
//    glGetIntegerv(GL_BLEND_SRC_RGB, (GLint*)&last_blend_src_rgb);
//    GLenum last_blend_dst_rgb;
//    glGetIntegerv(GL_BLEND_DST_RGB, (GLint*)&last_blend_dst_rgb);
//    GLenum last_blend_src_alpha;
//    glGetIntegerv(GL_BLEND_SRC_ALPHA, (GLint*)&last_blend_src_alpha);
//    GLenum last_blend_dst_alpha;
//    glGetIntegerv(GL_BLEND_DST_ALPHA, (GLint*)&last_blend_dst_alpha);
//    GLenum last_blend_equation_rgb;
//    glGetIntegerv(GL_BLEND_EQUATION_RGB, (GLint*)&last_blend_equation_rgb);
//    GLenum last_blend_equation_alpha;
//    glGetIntegerv(GL_BLEND_EQUATION_ALPHA, (GLint*)&last_blend_equation_alpha);
//    GLboolean last_enable_blend = glIsEnabled(GL_BLEND);
//    GLboolean last_enable_cull_face = glIsEnabled(GL_CULL_FACE);
//    GLboolean last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
//    GLboolean last_enable_scissor_test = glIsEnabled(GL_SCISSOR_TEST);
//
//    glEnable(GL_CULL_FACE);
//    // activate corresponding render state	
//    glBindVertexArray(vao);
//    shader.Use();
//    glUniform3f(glGetUniformLocation(shader.GetHandle(), "textColor"), colour.x, colour.y, colour.z);
//    glm::mat4 mat(1.0f);
//    mat = glm::rotate(mat, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
//
//    int v_screen_width = 1280;
//    int v_screen_height = 720;
//
//    glm::mat4 projection = glm::ortho(0.0f, (float)v_screen_width, 0.0f, (float)v_screen_height);
//    mat = projection * mat;
//    //shader.SetMat4f("projection", mat);
//    //shader.SetVec3f("textColour", colour);
//    glActiveTexture(GL_TEXTURE0);
//
//    //Iterate through all characters
//    for (auto iter = text.begin(); iter != text.end(); iter++)
//    {
//        Character ch = characters[*iter];
//
//        //x position
//        GLfloat xpos = x + ch.bearing.x * scale;
//
//        //y position
//        GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;
//
//        //width
//        GLfloat width = ch.size.x * scale;
//
//        //height 
//        GLfloat height = ch.size.y * scale;
//
//        //update VBO for each character based on real-time
//        GLfloat vertices[6][4] =
//        {
//            //position( , ) , text_coordinate( , )
//            {xpos, (ypos + height) , 0.0, 0.0},
//            {xpos, ypos, 0.0, 1.0},
//            {(xpos + width), ypos, 1.0, 1.0},
//            {xpos, (ypos + height), 0.0, 0.0},
//            {xpos + width, ypos, 1.0, 1.0},
//            {xpos + width, ypos + height, 1.0, 0.0}
//        };
//
//        //Render glyph texture over quad
//        glBindTexture(GL_TEXTURE_2D, ch.texture_ID);
//        // Update content of VBO memory
//        glBindBuffer(GL_ARRAY_BUFFER, vbo);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//
//        // Be sure to use glBufferSubData and not glBufferData
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//        // Render quad
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//
//        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//        x += (ch.advance >> 6) * scale; // Bitshifts by 6 to get value in pixels (2^6 = 64)
//    }
//    glBindVertexArray(0);
//    glBindTexture(GL_TEXTURE_2D, 0);
//
//    // Restore modified GL state
//    glUseProgram(last_program);
//    glBindTexture(GL_TEXTURE_2D, last_texture);
//    glBindSampler(0, last_sampler);
//    glActiveTexture(last_active_texture);
//    glBindVertexArray(last_vertex_array);
//    glBindBuffer(GL_ARRAY_BUFFER, last_array_buffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer);
//    glBlendEquationSeparate(last_blend_equation_rgb, last_blend_equation_alpha);
//    glBlendFuncSeparate(last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha);
//
//    if (last_enable_blend)
//        glEnable(GL_BLEND);
//    else
//        glDisable(GL_BLEND);
//    if (last_enable_cull_face)
//        glEnable(GL_CULL_FACE);
//    else
//        glDisable(GL_CULL_FACE);
//    if (last_enable_depth_test)
//        glEnable(GL_DEPTH_TEST);
//    else
//        glDisable(GL_DEPTH_TEST);
//    if (last_enable_scissor_test)
//        glEnable(GL_SCISSOR_TEST);
//    else
//        glDisable(GL_SCISSOR_TEST);
//
//    glPolygonMode(GL_FRONT_AND_BACK, last_polygon_mode[0]);
//    glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
//    glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
//
//}
};