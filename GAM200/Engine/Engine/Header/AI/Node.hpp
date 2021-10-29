/* Start Header**********************************************************************************/
/*
@file    Node.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    29/10/2021
\brief
#include "Engine/Header/AI/Node.hpp"
This file contain the declaration of Node


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef NODE_H
#define NODE_H

#include "Engine/Header/Math/MathLib.hpp"
#include <vector>

namespace Engine {
	namespace AI {
		struct Node {
			int x, y;
			Math::ivec2 pos;
			bool obstacle = false;
			bool visited = false;
			float globalGoal;
			float localGoal;
			
			Node* parent;
			std::vector<Node*> neighbours;
		};
	}
}

#endif