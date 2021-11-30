/* Start Header**********************************************************************************/
/*
@file    Mesh.hpp
@author  Chia Yi Da		c.yida@digipen.edu  100%
@date    16/06/2021
\brief
This file contains the declaration of function that sets up the dynamic buffers of vertices and
ebo for batch rendering.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef MESH_H
#define MESH_H

#include "Engine/Header/Management/ResourceManager.hpp"

namespace Engine
{
    namespace GraphicImplementation
    {
        class Renderer
        {
        public:
            // Functions for GraphicSystem
            static void Init();
            static void Shutdown();
            static void BeginBatch();

            static void DrawQuad(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation, const Math::vec4 color);
            static void DrawQuad(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation, const uint32_t textureID, 
                const Math::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f},
                Math::vec2 _min = { 0.01f, 0.01f }, Math::vec2 _max = { 0.99f, 0.99f });

            static void DrawQuadDebug(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation, const Math::vec4 color);
            static void DrawCircleDebug(const Math::vec2& tposition, const Math::vec2 tscale, const Math::vec4 color);
            static void DrawLines(const Math::vec2& position1, const Math::vec2& position2, const Math::vec4 color = {0.0f, 1.0f, 0.0f, 1.0f});

            // Font functions for FontSystem
            static void InitFont();
            static void DestroyFont();
            static void BeginFontBatch();

            // End batch functions
            static void EndQuadBatch();
            static void EndQuadDebugBatch();
            static void EndCircleDebugBatch();
            static void EndLinesBatch();
            static void EndFontBatch();

            // Flush batch functions
            static void FlushQuad();
            static void FlushQuadDebug();
            static void FlushCircleDebug();
            static void FlushLines();
            static void FlushFont();

            static void DrawString(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation,
                const std::string font, const std::string text, const Math::vec4 _colour);

            static void ResetFontStats();

            // Struct declaration
            struct Stats
            {
                uint32_t drawCount = 0;
                uint32_t quadCount = 0;
                uint32_t quadDebugCount = 0;
                uint32_t circleDebugCount = 0;
                uint32_t fontCount = 0;
                uint32_t linesCount = 0;
            };

            // Getter functions for stats
            static const Stats& GetQuadStats();
            static const Stats& GetQuadDebugStats();
            static const Stats& GetCircleDebugStats();
            static const Stats& GetFontStats();
            static const Stats& GetLinesStats();

            static void ResetStats();

        private:
            static void InitQuad();
            static void InitCircle();
            static void InitQuadDebug();
            static void InitCircleDebug();
            static void InitLines();

            static void DestroyQuad();
            static void DestroyQuadDebug();
            static void DestroyCircleDebug();
            static void DestroyLines();

            static void BeginQuadBatch();
            static void BeginQuadDebugBatch();
            static void BeginCircleDebugBatch();
            static void BeginLinesBatch();

            static void ResetQuadStats();
            static void ResetQuadDebugStats();
            static void ResetCircleDebugStats();
            static void ResetLinesStats();
        };
    }
}

#endif // MESH_H