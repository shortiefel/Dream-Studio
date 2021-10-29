/* Start Header**********************************************************************************/
/*
@file    AISystem.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    29/10/2021
\brief
#include "Engine/Header/AI/AISystem.hpp"
This file contain the declaration of AISystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GRID_H
#define GRID_H

#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"
#include "Engine/Header/AI/Node.hpp"

#include "Engine/Header/ECS/System/CameraSystem.hpp"
#include "Engine/Header/Graphic/FrameBuffer.hpp"

namespace Engine {
	namespace AI {
		class AISystem : public Singleton<AISystem> {
		public:
			void CreateGrid(Math::ivec2 _mapSize, Math::ivec2 _tileSize);
			void AStar_Algorithm(Node* nodeStart, Node* nodeEnd);
			void Render(Math::mat3 camMatrix = CameraSystem::GetInstance().GetTransformUI(), Graphic::FrameBuffer* _fbo = nullptr);
			void SetRender();
			void Reset();

		private:
			//Number of tiles in x and y
			Math::ivec2 mapSize{};
			//Height and length of a single tile
			Math::ivec2 tileSize{};

			Node* nodes = nullptr;

			bool render = false;
			bool created = false;

			SINGLETON_SETUP(AISystem);
		};
	}
}

#endif