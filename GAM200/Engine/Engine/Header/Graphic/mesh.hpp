/* Start Header**********************************************************************************/
/*
@file    mesh.hpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    16/06/2021
\brief
This file contains the declaration of functions that sets up the vao of meshes


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef MESH_H
#define MESH_H

#include "Engine/Header/Graphic/glslshader.hpp" // for GLSLShader
#include "Engine/Header/pch.hpp"
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/Math/Vector2D.hpp"

namespace Engine {
    namespace GraphicImplementation {
        // container that contains 3 different vectors of vertex coordinates
        // Object Position, Color and Texture Coordinates respectively
        struct GLMesh {
            MathD::Vec2 objPos_vtx;
            MathD::Vec3 clr_vtx;
            MathD::Vec2 texPos_vtx;
        };        
        
        void setup_vao();
    }
}



#endif // MESH_H