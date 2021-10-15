/* Start Header**********************************************************************************/
/*
@file    Mesh.hpp
@author  Chia Yi Da		chiayida98@gmail.com
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

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine
{
    namespace GraphicImplementation
    {
        class Renderer
        {
        public:
            static void Init();
            static void Shutdown();

            static void BeginBatch(bool debugdraw);
            static void EndBatch(bool debugdraw);

            static void Flush(bool debugdraw);

            static void DrawQuad(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation, const Math::vec3 color);
            static void DrawQuad(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation, const uint32_t textureID);

            static void DrawQuadDebug(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation);
            static void DrawCircleDebug(const Math::vec2& tposition, const Math::vec2 tscale, const float trotation);

            struct Stats
            {
                uint32_t drawCount = 0;
                uint32_t quadCount = 0;
                uint32_t quadDebugCount = 0;
                uint32_t circleDebugCount = 0;
            };

            static const Stats& GetQuadStats();
            static const Stats& GetQuadDebugStats();
            static const Stats& GetCircleDebugStats();

            static void ResetStats();

        private:
            static void InitQuad();
            static void InitCircle();
            static void InitQuadDebug();
            static void InitCircleDebug();

            static void BeginQuadBatch();
            static void BeginQuadDebugBatch();
            static void BeginCircleDebugBatch();

            static void EndQuadBatch();
            static void EndQuadDebugBatch();
            static void EndCircleDebugBatch();

            static void FlushQuad();
            static void FlushQuadDebug();
            static void FlushCircleDebug();
        };
    }
}

#endif // MESH_H