/* Start Header**********************************************************************************/
/*
@file    Mesh.cpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    16/06/2021
\brief
This file contains the definition of function that sets up the dynamic buffers of vertices and
ebo for batch rendering.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include <vector>
#include "Engine/Header/Graphic/Mesh.hpp"
#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/Graphic/GLSLShader.hpp"

#pragma warning( push )
#pragma warning( disable : 28020 )

namespace Engine
{
    namespace GraphicImplementation
    {
        // Change to what is best suited
#define MAXQUADCOUNT 500 // how many quads per buffer
#define MAXCIRCLECOUNT 50 // how many circles per buffer
#define CIRCLESLICES 20 // how circular the shape will be, larger = more circlular.

// Initialise variables
        static const size_t stMaxQuadCount = MAXQUADCOUNT;
        static const size_t stOneQuadVertex = 4;
        static const size_t stOneQuadIndex = stOneQuadVertex + 2;
        static const size_t stMaxQuadVertexCount = stMaxQuadCount * stOneQuadVertex;
        static const size_t stMaxQuadIndexCount = stMaxQuadCount * stOneQuadIndex;

        // Debug draws of objects
        static const size_t stMaxQuadDebugCount = MAXQUADCOUNT;
        static const size_t stOneQuadDebugVertex = 4;
        static const size_t stOneQuadDebugIndex = stOneQuadDebugVertex * 2;
        static const size_t stMaxQuadDebugVertexCount = stMaxQuadDebugCount * stOneQuadDebugVertex;
        static const size_t stMaxQuadDebugIndexCount = stMaxQuadDebugCount * stOneQuadDebugIndex;

        static const size_t stMaxCircleDebugCount = MAXCIRCLECOUNT;
        static const size_t stOneCircleDebugVertex = CIRCLESLICES;
        static const size_t stOneCircleDebugIndex = stOneCircleDebugVertex * 2;
        static const size_t stMaxCircleDebugVertexCount = stMaxCircleDebugCount * stOneCircleDebugVertex;
        static const size_t stMaxCircleDebugIndexCount = stMaxCircleDebugCount * stOneCircleDebugIndex;

        static const size_t stMaxTextures = 32;

        struct GLMesh
        {
            Math::vec2 position;
            Math::vec3 color;
            Math::vec2 texCoords;
            float texID{};

            Math::vec2 tposition;
            Math::vec2 tscale;
            float trotation{};

            int entityId;
        };

        struct RendererData
        {
            GLuint va = 0; //vertex array
            GLuint vb = 0; //vertex buffer
            GLuint ib = 0; //index buffer

            // first slot is for object without colors
            GLuint whitetexture = 0;
            uint32_t whitetextureslot = 0;

            uint32_t indexcount = 0;

            GLMesh* vertexbuffer = nullptr;
            GLMesh* vertexbufferptr = nullptr;

            std::array<uint32_t, stMaxTextures> arrTextureSlots{};
            uint32_t uiTextureSlotIndex = 1; // 0 = white texture (aka no texture)

            Renderer::Stats renderStats;
        };

        static RendererData s_QuadData;
        static RendererData s_QuadDebugData;
        static RendererData s_CircleDebugData;

        void Renderer::InitQuad()
        {
            if (s_QuadData.vertexbuffer != nullptr)
            {
                return;
            }

            s_QuadData.vertexbuffer = new GLMesh[stMaxQuadVertexCount];

            glCreateVertexArrays(1, &s_QuadData.va);
            glBindVertexArray(s_QuadData.va);

            glCreateBuffers(1, &s_QuadData.vb);
            glBindBuffer(GL_ARRAY_BUFFER, s_QuadData.vb);
            glBufferData(GL_ARRAY_BUFFER, stMaxQuadVertexCount * sizeof(GLMesh), nullptr, GL_DYNAMIC_DRAW);

            glEnableVertexArrayAttrib(s_QuadData.va, 0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, position));

            glEnableVertexArrayAttrib(s_QuadData.va, 1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, color));

            glEnableVertexArrayAttrib(s_QuadData.va, 2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, texCoords));

            glEnableVertexArrayAttrib(s_QuadData.va, 3);
            glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, texID));

            glEnableVertexArrayAttrib(s_QuadData.va, 4);
            glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, tposition));

            glEnableVertexArrayAttrib(s_QuadData.va, 5);
            glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, tscale));

            glEnableVertexArrayAttrib(s_QuadData.va, 6);
            glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, trotation));

            /*
            example of indices loop; 2 triangles to form a quad:
                0, 1, 2,    -> First triangle
                2, 3, 0     -> Second triangle

                4, 5, 6,
                6, 7, 4

                and so forth...
            */

            uint32_t indices[stMaxQuadIndexCount];
            uint32_t offset = 0;

            for (int i = 0; i < stMaxQuadIndexCount; i += stOneQuadIndex)
            {
                indices[i + 0] = 0 + offset;
                indices[i + 1] = 1 + offset;
                indices[i + 2] = 2 + offset;

                indices[i + 3] = 2 + offset;
                indices[i + 4] = 3 + offset;
                indices[i + 5] = 0 + offset;

                offset += stOneQuadVertex;
            }

            glCreateBuffers(1, &s_QuadData.ib);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_QuadData.ib);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // 1x1 white texture
            glCreateTextures(GL_TEXTURE_2D, 1, &s_QuadData.whitetexture);
            glBindTexture(GL_TEXTURE_2D, s_QuadData.whitetexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            uint32_t color = 0xffffffff; // white color
            //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, 1, 1, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, &color);

            // set all texture slots to 0
            s_QuadData.arrTextureSlots[0] = s_QuadData.whitetexture;
            for (size_t i = 1; i < stMaxTextures; i++)
            {
                s_QuadData.arrTextureSlots[i] = 0;
            }
        }

        void Renderer::InitQuadDebug()
        {
            if (s_QuadDebugData.vertexbuffer != nullptr)
            {
                return;
            }

            s_QuadDebugData.vertexbuffer = new GLMesh[stMaxQuadDebugVertexCount];

            glCreateVertexArrays(1, &s_QuadDebugData.va);
            glBindVertexArray(s_QuadDebugData.va);

            glCreateBuffers(1, &s_QuadDebugData.vb);
            glBindBuffer(GL_ARRAY_BUFFER, s_QuadDebugData.vb);
            glBufferData(GL_ARRAY_BUFFER, stMaxQuadDebugVertexCount * sizeof(GLMesh), nullptr, GL_DYNAMIC_DRAW);

            glEnableVertexArrayAttrib(s_QuadDebugData.va, 0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, position));

            glEnableVertexArrayAttrib(s_QuadDebugData.va, 1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, color));

            glEnableVertexArrayAttrib(s_QuadDebugData.va, 2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, texCoords));

            glEnableVertexArrayAttrib(s_QuadDebugData.va, 3);
            glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, texID));

            glEnableVertexArrayAttrib(s_QuadDebugData.va, 4);
            glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, tposition));

            glEnableVertexArrayAttrib(s_QuadDebugData.va, 5);
            glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, tscale));

            glEnableVertexArrayAttrib(s_QuadDebugData.va, 6);
            glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, trotation));

            /*
            example of indices loop; 4 lines to draw a quad:
                0, 1        -> first line, horizontal bottom
                1, 2        -> second line, right vertical
                2, 3        -> third line, horizontal top
                3, 0        -> fourth line, left vertical

                4, 5
                5, 6
                6, 7
                7, 0

                and so forth...
            */

            uint32_t indices[stMaxQuadDebugIndexCount];
            uint32_t offset = 0;

            for (int i = 0; i < stMaxQuadDebugIndexCount; i += stOneQuadDebugIndex)
            {
                indices[i + 0] = 0 + offset;
                indices[i + 1] = 1 + offset;

                indices[i + 2] = 1 + offset;
                indices[i + 3] = 2 + offset;

                indices[i + 4] = 2 + offset;
                indices[i + 5] = 3 + offset;

                indices[i + 6] = 3 + offset;
                indices[i + 7] = 0 + offset;

                offset += stOneQuadDebugVertex;
            }


            glCreateBuffers(1, &s_QuadDebugData.ib);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_QuadDebugData.ib);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // 1x1 white texture
            glCreateTextures(GL_TEXTURE_2D, 1, &s_QuadDebugData.whitetexture);
            glBindTexture(GL_TEXTURE_2D, s_QuadDebugData.whitetexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            uint32_t color = 0xffffffff; // white color
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

            s_QuadDebugData.arrTextureSlots[0] = s_QuadDebugData.whitetexture;
            for (size_t i = 1; i < stMaxTextures; i++)
            {
                s_QuadDebugData.arrTextureSlots[i] = 0;
            }
        }

        void Renderer::InitCircleDebug()
        {
            if (s_CircleDebugData.vertexbuffer != nullptr)
            {
                return;
            }

            s_CircleDebugData.vertexbuffer = new GLMesh[stMaxCircleDebugVertexCount];

            glCreateVertexArrays(1, &s_CircleDebugData.va);
            glBindVertexArray(s_CircleDebugData.va);

            glCreateBuffers(1, &s_CircleDebugData.vb);
            glBindBuffer(GL_ARRAY_BUFFER, s_CircleDebugData.vb);
            glBufferData(GL_ARRAY_BUFFER, stMaxCircleDebugVertexCount * sizeof(GLMesh), nullptr, GL_DYNAMIC_DRAW);

            glEnableVertexArrayAttrib(s_CircleDebugData.va, 0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, position));

            glEnableVertexArrayAttrib(s_CircleDebugData.va, 1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, color));

            glEnableVertexArrayAttrib(s_CircleDebugData.va, 2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, texCoords));

            glEnableVertexArrayAttrib(s_CircleDebugData.va, 3);
            glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, texID));

            glEnableVertexArrayAttrib(s_CircleDebugData.va, 4);
            glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, tposition));

            glEnableVertexArrayAttrib(s_CircleDebugData.va, 5);
            glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, tscale));

            glEnableVertexArrayAttrib(s_CircleDebugData.va, 6);
            glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, trotation));

            uint32_t indices[stMaxCircleDebugIndexCount];
            uint32_t offset = 0;

            /*
            example of indices loop for line circle;
                0, 1    -> first line
                1, 2    -> second line
                2, 3    -> third line
                3, 4    -> fourth line
                4, 5    -> fifth line (second index of circle)
                5, 0    -> last line (connect last index to first index)
            */

            for (int i = 0; i < stMaxCircleDebugIndexCount; i += stOneCircleDebugIndex)
            {
                for (int j = 0, k = 0; k < CIRCLESLICES; j++, k++)
                {
                    indices[i + j] = k + offset;

                    if (j < (stOneCircleDebugIndex - 2))
                    {
                        indices[i + ++j] = k + 1 + offset;
                    }
                    else
                    {
                        // line from last index to first index
                        indices[i + j] = k + offset;
                        indices[i + j + 1] = 0 + offset;
                    }
                }
                offset += stOneCircleDebugVertex;
            }

            glCreateBuffers(1, &s_CircleDebugData.ib);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_CircleDebugData.ib);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // 1x1 white texture
            glCreateTextures(GL_TEXTURE_2D, 1, &s_CircleDebugData.whitetexture);
            glBindTexture(GL_TEXTURE_2D, s_CircleDebugData.whitetexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            uint32_t color = 0xffffffff; // white color
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

            s_CircleDebugData.arrTextureSlots[0] = s_CircleDebugData.whitetexture;
            for (size_t i = 1; i < stMaxTextures; i++)
            {
                s_CircleDebugData.arrTextureSlots[i] = 0;
            }
        }

        void Renderer::Init()
        {
            InitQuad();

            InitQuadDebug();
            InitCircleDebug();
        }

        void Renderer::Shutdown()
        {
            glDeleteVertexArrays(1, &s_QuadData.va);
            glDeleteBuffers(1, &s_QuadData.vb);
            glDeleteBuffers(1, &s_QuadData.ib);

            glDeleteVertexArrays(1, &s_QuadDebugData.va);
            glDeleteBuffers(1, &s_QuadDebugData.vb);
            glDeleteBuffers(1, &s_QuadDebugData.ib);

            glDeleteVertexArrays(1, &s_CircleDebugData.va);
            glDeleteBuffers(1, &s_CircleDebugData.vb);
            glDeleteBuffers(1, &s_CircleDebugData.ib);

            glDeleteTextures(1, &s_QuadData.whitetexture);
            glDeleteTextures(1, &s_QuadDebugData.whitetexture);
            glDeleteTextures(1, &s_CircleDebugData.whitetexture);

            delete[] s_QuadData.vertexbuffer;
            delete[] s_QuadDebugData.vertexbuffer;
            delete[] s_CircleDebugData.vertexbuffer;
        }

        void Renderer::BeginQuadBatch()
        {
            s_QuadData.vertexbufferptr = s_QuadData.vertexbuffer;
        }

        void Renderer::BeginQuadDebugBatch()
        {
            s_QuadDebugData.vertexbufferptr = s_QuadDebugData.vertexbuffer;
        }

        void Renderer::BeginCircleDebugBatch()
        {
            s_CircleDebugData.vertexbufferptr = s_CircleDebugData.vertexbuffer;
        }

        void Renderer::BeginBatch(bool debugdraw)
        {
            BeginQuadBatch();

            if (debugdraw == GL_TRUE)
            {
                BeginQuadDebugBatch();
                BeginCircleDebugBatch();
            }
        }

        void Renderer::EndQuadBatch()
        {
            GLsizeiptr sizeQuad = (uint8_t*)s_QuadData.vertexbufferptr - (uint8_t*)s_QuadData.vertexbuffer;
            glBindBuffer(GL_ARRAY_BUFFER, s_QuadData.vb);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeQuad, s_QuadData.vertexbuffer);
        }

        void Renderer::EndQuadDebugBatch()
        {
            GLsizeiptr sizeQuadDebug = (uint8_t*)s_QuadDebugData.vertexbufferptr - (uint8_t*)s_QuadDebugData.vertexbuffer;
            glBindBuffer(GL_ARRAY_BUFFER, s_QuadDebugData.vb);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeQuadDebug, s_QuadDebugData.vertexbuffer);
        }

        void Renderer::EndCircleDebugBatch()
        {
            GLsizeiptr sizeCircleDebug = (uint8_t*)s_CircleDebugData.vertexbufferptr - (uint8_t*)s_CircleDebugData.vertexbuffer;
            glBindBuffer(GL_ARRAY_BUFFER, s_CircleDebugData.vb);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeCircleDebug, s_CircleDebugData.vertexbuffer);
        }

        void Renderer::EndBatch(bool debugdraw)
        {
            EndQuadBatch();

            if (debugdraw == GL_TRUE)
            {
                EndQuadDebugBatch();
                EndCircleDebugBatch();
            }
        }

        void Renderer::FlushQuad()
        {
            for (uint32_t i = 0; i < s_QuadData.uiTextureSlotIndex; i++)
            {
                glBindTextureUnit(i, s_QuadData.arrTextureSlots[i]);
            }
            glBindVertexArray(s_QuadData.va);

            glDrawElements(GL_TRIANGLES, s_QuadData.indexcount, GL_UNSIGNED_INT, nullptr);
            s_QuadData.renderStats.drawCount++;

            s_QuadData.indexcount = 0;
            s_QuadData.uiTextureSlotIndex = 1;
        }

        void Renderer::FlushQuadDebug()
        {
            for (uint32_t i = 0; i < s_QuadDebugData.uiTextureSlotIndex; i++)
            {
                glBindTextureUnit(i, s_QuadDebugData.arrTextureSlots[i]);
            }
            glBindVertexArray(s_QuadDebugData.va);

            glDrawElements(GL_LINES, s_QuadDebugData.indexcount, GL_UNSIGNED_INT, nullptr);
            s_QuadDebugData.renderStats.drawCount++;

            s_QuadDebugData.indexcount = 0;
            s_QuadDebugData.uiTextureSlotIndex = 1;
        }

        void Renderer::FlushCircleDebug()
        {
            for (uint32_t i = 0; i < s_CircleDebugData.uiTextureSlotIndex; i++)
            {
                glBindTextureUnit(i, s_CircleDebugData.arrTextureSlots[i]);
            }
            glBindVertexArray(s_CircleDebugData.va);

            glDrawElements(GL_LINES, s_CircleDebugData.indexcount, GL_UNSIGNED_INT, nullptr);
            s_CircleDebugData.renderStats.drawCount++;

            s_CircleDebugData.indexcount = 0;
            s_CircleDebugData.uiTextureSlotIndex = 1;
        }

        void Renderer::Flush(bool debugdraw)
        {
            FlushQuad();

            if (debugdraw == GL_TRUE)
            {
                glLineWidth(5.f);

                FlushQuadDebug();
                FlushCircleDebug();

                glLineWidth(1.f);
            }

        }

        void Renderer::DrawQuad(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation,
            const Math::vec3 color)
        {
            if (s_QuadData.indexcount >= stMaxQuadIndexCount)
            {
                EndQuadBatch();
                FlushQuad();
                BeginQuadBatch();
            }

            float textureIndex = 0.0f;
            Math::vec2 position = { -1.f, -1.f };
            Math::vec2 size = { 2.f, 2.f };

            s_QuadData.vertexbufferptr->position = { position.x, position.y };
            s_QuadData.vertexbufferptr->color = color;
            s_QuadData.vertexbufferptr->texCoords = { 0.0f, 0.0f };
            s_QuadData.vertexbufferptr->texID = textureIndex;
            s_QuadData.vertexbufferptr->tposition = tposition;
            s_QuadData.vertexbufferptr->tscale = tscale;
            s_QuadData.vertexbufferptr->trotation = Math::radians(trotation);
            s_QuadData.vertexbufferptr++;

            s_QuadData.vertexbufferptr->position = { position.x + size.x, position.y };
            s_QuadData.vertexbufferptr->color = color;
            s_QuadData.vertexbufferptr->texCoords = { 1.0f, 0.0f };
            s_QuadData.vertexbufferptr->texID = textureIndex;
            s_QuadData.vertexbufferptr->tposition = tposition;
            s_QuadData.vertexbufferptr->tscale = tscale;
            s_QuadData.vertexbufferptr->trotation = Math::radians(trotation);
            s_QuadData.vertexbufferptr++;

            s_QuadData.vertexbufferptr->position = { position.x + size.x, position.y + size.y };
            s_QuadData.vertexbufferptr->color = color;
            s_QuadData.vertexbufferptr->texCoords = { 1.0f, 1.0f };
            s_QuadData.vertexbufferptr->texID = textureIndex;
            s_QuadData.vertexbufferptr->tposition = tposition;
            s_QuadData.vertexbufferptr->tscale = tscale;
            s_QuadData.vertexbufferptr->trotation = Math::radians(trotation);
            s_QuadData.vertexbufferptr++;

            s_QuadData.vertexbufferptr->position = { position.x, position.y + size.y };
            s_QuadData.vertexbufferptr->color = color;
            s_QuadData.vertexbufferptr->texCoords = { 0.0f, 1.0f };
            s_QuadData.vertexbufferptr->texID = textureIndex;
            s_QuadData.vertexbufferptr->tposition = tposition;
            s_QuadData.vertexbufferptr->tscale = tscale;
            s_QuadData.vertexbufferptr->trotation = Math::radians(trotation);
            s_QuadData.vertexbufferptr++;

            s_QuadData.indexcount += stOneQuadIndex;
            s_QuadData.renderStats.quadCount++;
        }

        void Renderer::DrawQuad(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation,
            const uint32_t textureID)
        {
            if (s_QuadData.indexcount >= stMaxQuadIndexCount || s_QuadData.uiTextureSlotIndex > 31)
            {
                EndQuadBatch();
                FlushQuad();
                BeginQuadBatch();
            }

            Math::vec3 color = { 1.0f, 1.0f, 1.0f };
            Math::vec2 position = { -1.f, -1.f };
            Math::vec2 size = { 2.f, 2.f };

            float textureIndex = 0.0f;
            for (uint32_t i = 1; i < s_QuadData.uiTextureSlotIndex; i++)
            {
                if (s_QuadData.arrTextureSlots[i] == textureID)
                {
                    textureIndex = (float)i;
                    break;
                }
            }

            if (textureIndex == 0.0f)
            {
                textureIndex = (float)s_QuadData.uiTextureSlotIndex;
                s_QuadData.arrTextureSlots[(size_t)textureIndex] = textureID;
                s_QuadData.uiTextureSlotIndex++;
            }

            s_QuadData.vertexbufferptr->position = { position.x, position.y };
            s_QuadData.vertexbufferptr->color = color;
            s_QuadData.vertexbufferptr->texCoords = { 0.0f, 0.0f };
            s_QuadData.vertexbufferptr->texID = textureIndex;
            s_QuadData.vertexbufferptr->tposition = tposition;
            s_QuadData.vertexbufferptr->tscale = tscale;
            s_QuadData.vertexbufferptr->trotation = Math::radians(trotation);
            s_QuadData.vertexbufferptr++;

            s_QuadData.vertexbufferptr->position = { position.x + size.x, position.y };
            s_QuadData.vertexbufferptr->color = color;
            s_QuadData.vertexbufferptr->texCoords = { 1.0f, 0.0f };
            s_QuadData.vertexbufferptr->texID = textureIndex;
            s_QuadData.vertexbufferptr->tposition = tposition;
            s_QuadData.vertexbufferptr->tscale = tscale;
            s_QuadData.vertexbufferptr->trotation = Math::radians(trotation);
            s_QuadData.vertexbufferptr++;

            s_QuadData.vertexbufferptr->position = { position.x + size.x, position.y + size.y };
            s_QuadData.vertexbufferptr->color = color;
            s_QuadData.vertexbufferptr->texCoords = { 1.0f, 1.0f };
            s_QuadData.vertexbufferptr->texID = textureIndex;
            s_QuadData.vertexbufferptr->tposition = tposition;
            s_QuadData.vertexbufferptr->tscale = tscale;
            s_QuadData.vertexbufferptr->trotation = Math::radians(trotation);
            s_QuadData.vertexbufferptr++;

            s_QuadData.vertexbufferptr->position = { position.x, position.y + size.y };
            s_QuadData.vertexbufferptr->color = color;
            s_QuadData.vertexbufferptr->texCoords = { 0.0f, 1.0f };
            s_QuadData.vertexbufferptr->texID = textureIndex;
            s_QuadData.vertexbufferptr->tposition = tposition;
            s_QuadData.vertexbufferptr->tscale = tscale;
            s_QuadData.vertexbufferptr->trotation = Math::radians(trotation);
            s_QuadData.vertexbufferptr++;

            s_QuadData.indexcount += stOneQuadIndex;
            s_QuadData.renderStats.quadCount++;
        }

        void Renderer::DrawQuadDebug(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation)
        {
            if (s_QuadDebugData.indexcount >= stMaxQuadDebugIndexCount)
            {
                EndQuadDebugBatch();
                FlushQuadDebug();
                BeginQuadDebugBatch();
            }

            Math::vec3 color = { 1.f, 0.f, 0.f };

            float textureIndex = 0.0f;
            Math::vec2 position = { -1.f, -1.f };
            Math::vec2 size = { 2.f, 2.f };

            s_QuadDebugData.vertexbufferptr->position = { position.x, position.y };
            s_QuadDebugData.vertexbufferptr->color = color;
            s_QuadDebugData.vertexbufferptr->texCoords = { 0.0f, 0.0f };
            s_QuadDebugData.vertexbufferptr->texID = textureIndex;
            s_QuadDebugData.vertexbufferptr->tposition = tposition;
            s_QuadDebugData.vertexbufferptr->tscale = tscale;
            s_QuadDebugData.vertexbufferptr->trotation = Math::radians(trotation);
            s_QuadDebugData.vertexbufferptr++;

            s_QuadDebugData.vertexbufferptr->position = { position.x + size.x, position.y };
            s_QuadDebugData.vertexbufferptr->color = color;
            s_QuadDebugData.vertexbufferptr->texCoords = { 0.0f, 0.0f };
            s_QuadDebugData.vertexbufferptr->texID = textureIndex;
            s_QuadDebugData.vertexbufferptr->tposition = tposition;
            s_QuadDebugData.vertexbufferptr->tscale = tscale;
            s_QuadDebugData.vertexbufferptr->trotation = Math::radians(trotation);
            s_QuadDebugData.vertexbufferptr++;

            s_QuadDebugData.vertexbufferptr->position = { position.x + size.x, position.y + size.y };
            s_QuadDebugData.vertexbufferptr->color = color;
            s_QuadDebugData.vertexbufferptr->texCoords = { 0.0f, 0.0f };
            s_QuadDebugData.vertexbufferptr->texID = textureIndex;
            s_QuadDebugData.vertexbufferptr->tposition = tposition;
            s_QuadDebugData.vertexbufferptr->tscale = tscale;
            s_QuadDebugData.vertexbufferptr->trotation = Math::radians(trotation);
            s_QuadDebugData.vertexbufferptr++;

            s_QuadDebugData.vertexbufferptr->position = { position.x, position.y + size.y };
            s_QuadDebugData.vertexbufferptr->color = color;
            s_QuadDebugData.vertexbufferptr->texCoords = { 0.0f, 0.0f };
            s_QuadDebugData.vertexbufferptr->texID = textureIndex;
            s_QuadDebugData.vertexbufferptr->tposition = tposition;
            s_QuadDebugData.vertexbufferptr->tscale = tscale;
            s_QuadDebugData.vertexbufferptr->trotation = Math::radians(trotation);
            s_QuadDebugData.vertexbufferptr++;

            s_QuadDebugData.indexcount += stOneQuadDebugIndex;
            s_QuadDebugData.renderStats.quadDebugCount++;
        }

        void Renderer::DrawCircleDebug(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation)
        {
            if (s_CircleDebugData.indexcount >= stMaxCircleDebugIndexCount)
            {
                EndCircleDebugBatch();
                FlushCircleDebug();
                BeginCircleDebugBatch();
            }

            Math::vec3 color = { 1.f, 0.f, 0.f };

            float textureIndex = 0.0f;

            // Number of vertices
            float rad = Math::radians(360.f / static_cast<float>(CIRCLESLICES));

            s_CircleDebugData.vertexbufferptr->position = { cos(rad * 1), sin(rad * 1) };
            s_CircleDebugData.vertexbufferptr->color = color;
            s_CircleDebugData.vertexbufferptr->texCoords = { 0.f, 0.f };
            s_CircleDebugData.vertexbufferptr->texID = textureIndex;
            s_CircleDebugData.vertexbufferptr->tposition = tposition;
            s_CircleDebugData.vertexbufferptr->tscale = tscale;
            s_CircleDebugData.vertexbufferptr->trotation = Math::radians(trotation);
            s_CircleDebugData.vertexbufferptr++;

            for (int i = 1, j = 2; i < stOneCircleDebugVertex; i++, j++)
            {
                s_CircleDebugData.vertexbufferptr->position = { cos(rad * j), sin(rad * j) };
                s_CircleDebugData.vertexbufferptr->color = color;
                s_CircleDebugData.vertexbufferptr->texCoords = { 0.f, 0.f };
                s_CircleDebugData.vertexbufferptr->texID = textureIndex;
                s_CircleDebugData.vertexbufferptr->tposition = tposition;
                s_CircleDebugData.vertexbufferptr->tscale = tscale;
                s_CircleDebugData.vertexbufferptr->trotation = Math::radians(trotation);
                s_CircleDebugData.vertexbufferptr++;
            }

            s_CircleDebugData.indexcount += stOneCircleDebugIndex;
            s_CircleDebugData.renderStats.circleDebugCount++;
        }

        const Renderer::Stats& Renderer::GetQuadStats()
        {
            return s_QuadData.renderStats;
        }

        const Renderer::Stats& Renderer::GetQuadDebugStats()
        {
            return s_QuadDebugData.renderStats;
        }

        const Renderer::Stats& Renderer::GetCircleDebugStats()
        {
            return s_CircleDebugData.renderStats;
        }

        void Renderer::ResetStats()
        {
            memset(&s_QuadData.renderStats, 0, sizeof(Stats));
            memset(&s_QuadDebugData.renderStats, 0, sizeof(Stats));
            memset(&s_CircleDebugData.renderStats, 0, sizeof(Stats));
        }
    }
}
#pragma warning (pop)


#if 0
void Renderer::InitCircle()
{
    if (s_CircleData.VertexBuffer != nullptr)
    {
        return;
    }

    s_CircleData.VertexBuffer = new GLMesh[MaxCircleVertexCount];

    glCreateVertexArrays(1, &s_CircleData.VA);
    glBindVertexArray(s_CircleData.VA);

    glCreateBuffers(1, &s_CircleData.VB);
    glBindBuffer(GL_ARRAY_BUFFER, s_CircleData.VB);
    glBufferData(GL_ARRAY_BUFFER, MaxCircleVertexCount * sizeof(GLMesh), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexArrayAttrib(s_CircleData.VA, 0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, position));

    glEnableVertexArrayAttrib(s_CircleData.VA, 1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, color));

    glEnableVertexArrayAttrib(s_CircleData.VA, 2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, texCoords));

    glEnableVertexArrayAttrib(s_CircleData.VA, 3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, texID));

    glEnableVertexArrayAttrib(s_CircleData.VA, 4);
    glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, tposition));

    glEnableVertexArrayAttrib(s_CircleData.VA, 5);
    glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, tscale));

    glEnableVertexArrayAttrib(s_CircleData.VA, 6);
    glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(GLMesh), (const void*)offsetof(GLMesh, trotation));

    /*
    example of indices loop:
        0, 1, 2,    -> First triangle
        2, 3, 0,    -> Second triangle

        4, 5, 6,    -> Third triangle
        6, 7, 0,    -> Fourth triangle

        ...

        till all the triangles forms a circle
    */

    uint32_t indices[MaxCircleIndexCount];
    uint32_t offset = 0;

    for (int i = 0; i < MaxCircleIndexCount; i += OneCircleIndex)
    {
        for (int j = 0, k = 0; j < OneCircleIndex; j += 6, k += 2)
        {
            indices[i + (j + 0)] = 0 + offset;
            indices[i + (j + 1)] = k + 1 + offset;
            indices[i + (j + 2)] = k + 2 + offset;
            indices[i + (j + 3)] = k + 2 + offset;
            indices[i + (j + 4)] = k + 3 + offset;
            indices[i + (j + 5)] = 0 + offset;
        }
        offset += OneCircleVertex;
    }


    glCreateBuffers(1, &s_CircleData.IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_CircleData.IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 1x1 white texture
    glCreateTextures(GL_TEXTURE_2D, 1, &s_CircleData.WhiteTexture);
    glBindTexture(GL_TEXTURE_2D, s_CircleData.WhiteTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    uint32_t color = 0xffffffff; // white color
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

    // set all texture slots to 0
    s_CircleData.TextureSlots[0] = s_CircleData.WhiteTexture;
    for (size_t i = 1; i < MaxTextures; i++)
    {
        s_CircleData.TextureSlots[i] = 0;
    }
}


void Renderer::DrawCircle(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation,
    Math::vec3 color)
{
    if (s_CircleData.IndexCount >= MaxCircleIndexCount || s_CircleData.TextureSlotIndex > 31)
    {
        EndCircleBatch();
        FlushCircle();
        BeginCircleBatch();
    }

    float textureIndex = 0.0f;

    // Number of vertices
    float rad = Math::radians(360.f / static_cast<float>(CIRCLESLICES));

    s_CircleData.VertexBufferPtr->position = { 0.f, 0.f };
    s_CircleData.VertexBufferPtr->color = color;
    s_CircleData.VertexBufferPtr->texCoords = { 0.5f, 0.5f };
    s_CircleData.VertexBufferPtr->texID = textureIndex;
    s_CircleData.VertexBufferPtr->tposition = tposition;
    s_CircleData.VertexBufferPtr->tscale = tscale;
    s_CircleData.VertexBufferPtr->trotation = Math::radians(trotation);
    s_CircleData.VertexBufferPtr++;

    for (int i = 1; i < OneCircleVertex; i++)
    {
        s_CircleData.VertexBufferPtr->position = { Math::vec2(cos(rad * i), sin(rad * i)) };
        s_CircleData.VertexBufferPtr->color = color;
        s_CircleData.VertexBufferPtr->texCoords = { 0.5f + cos(rad * i), 0.5f + sin(rad * i) };
        s_CircleData.VertexBufferPtr->texID = textureIndex;
        s_CircleData.VertexBufferPtr->tposition = tposition;
        s_CircleData.VertexBufferPtr->tscale = tscale;
        s_CircleData.VertexBufferPtr->trotation = Math::radians(trotation);
        s_CircleData.VertexBufferPtr++;
    }

    s_CircleData.IndexCount += OneCircleIndex;
    s_CircleData.RendererStats.CircleCount++;
}

void Renderer::DrawCircle(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation,
    const uint32_t textureID)
{
    if (s_CircleData.IndexCount >= MaxCircleIndexCount || s_CircleData.TextureSlotIndex > 31)
    {
        EndCircleBatch();
        FlushCircle();
        BeginCircleBatch();
    }

    Math::vec3 color = { 1.0f, 1.0f, 1.0f };

    float textureIndex = 0.0f;
    for (uint32_t i = 1; i < s_CircleData.TextureSlotIndex; i++)
    {
        if (s_CircleData.TextureSlots[i] == textureID)
        {
            textureIndex = (float)i;
            break;
        }
    }


    if (textureIndex == 0.0f)
    {
        textureIndex = (float)s_CircleData.TextureSlotIndex;
        s_CircleData.TextureSlots[(size_t)textureIndex] = textureID;
        s_CircleData.TextureSlotIndex++;
    }

    // Number of vertices
    float rad = Math::radians(360.f / static_cast<float>(CIRCLESLICES));

    s_CircleData.VertexBufferPtr->position = { cos(rad * 1), sin(rad * 1) };
    s_CircleData.VertexBufferPtr->color = color;
    s_CircleData.VertexBufferPtr->texCoords = { 0.5f, 0.5f };
    s_CircleData.VertexBufferPtr->texID = textureIndex;
    s_CircleData.VertexBufferPtr->tposition = tposition;
    s_CircleData.VertexBufferPtr->tscale = tscale;
    s_CircleData.VertexBufferPtr->trotation = Math::radians(trotation);
    s_CircleData.VertexBufferPtr++;

    for (int i = 1; i < OneCircleVertex; i++)
    {
        s_CircleData.VertexBufferPtr->position = { Math::vec2(cos(rad * i), sin(rad * i)) };
        s_CircleData.VertexBufferPtr->color = color;
        s_CircleData.VertexBufferPtr->texCoords = { 0.5f + cos(rad * i), 0.5f + sin(rad * i) };
        s_CircleData.VertexBufferPtr->texID = textureIndex;
        s_CircleData.VertexBufferPtr->tposition = tposition;
        s_CircleData.VertexBufferPtr->tscale = tscale;
        s_CircleData.VertexBufferPtr->trotation = Math::radians(trotation);
        s_CircleData.VertexBufferPtr++;
    }

    s_CircleData.IndexCount += OneCircleIndex;
    s_CircleData.RendererStats.CircleCount++;
}

#endif