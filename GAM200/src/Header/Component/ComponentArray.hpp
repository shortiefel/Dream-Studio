/* Start Header**********************************************************************************/
/*!
\file ComponentArray.hpp
\team name
\software name
\authors
NAME							EMAIL									ROLE
Tan Wei Ling Felicia			weilingfelicia.tan@digipen.edu			PRODUCER
Goh	See Yong Denise				2001220@sit.singaporetech.edu.sg
Ow Jian Wen						jianwen123321@hotmail.com				TECHINCAL DIRECTOR
Chia Yi Da						chiayida98@gmail.com
Margaret Teo Boon See			Teo.b@digipen.edu
Wang Ao							Ao.Wang@digipen.edu
Ng Jia Yi						Jiayi.ng@digipen.edu
\date 26/04/2021
\brief

To create a data structure that is a simple array with no holes. It contains the mapping from
entity IDs to array indices. When accessing array, it uses entity ID to look up the actual array index 
but when destroyed, it takes the last elemet of array and move into deleted entity's spott and update
the map

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#pragma once

#include "../Global.hpp"
#include <array>
#include <cassert>
#include <unordered_map>

class ComponentArrayInterface
{
	public:
		virtual ~ComponentArrayInterface() = default; //for it to be used everywhere i think ?
		virtual void EntityDestroyed(Entity entity) = 0; //tells my array its destroyed and it needs to update array mapping
};

