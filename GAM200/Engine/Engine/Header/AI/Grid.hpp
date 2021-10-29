/* Start Header**********************************************************************************/
/*
@file    Grid.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    29/10/2021
\brief
#include "Engine/Header/AI/Grid.hpp"
This file contain the declaration of Grid


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GRID_H
#define GRID_H

#include "Engine/Header/Math/MathLib.hpp"

namespace Engine {
	namespace AI {
		class Grid {
		public:
		private:
			//Number of tiles in x and y
			Math::ivec2 mapSize{};
			//Height and length of a single tile
			Math::ivec2 tileSize{};
		};
	}
}

#endif