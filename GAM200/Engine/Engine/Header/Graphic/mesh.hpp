/* Start Header**********************************************************************************/
/*
@file    mesh.hpp
@author  Chia Yi Da		chiayida98@gmail.com
@date    16/06/2021
\brief
This file contains the declaration of function that sets up the vao of different meshes


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef MESH_H
#define MESH_H

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
    namespace GraphicImplementation {
        // container that contains 3 different vectors of vertex coordinates
        // Object position, color and 
        // Texture coordinates respectively
        struct GLMesh {
            Math::vec2 objPos_vtx;
            Math::vec3 clr_vtx;
            Math::vec2 texPos_vtx;
        };        
        
        void setup_vao();
    }
}

#endif // MESH_H