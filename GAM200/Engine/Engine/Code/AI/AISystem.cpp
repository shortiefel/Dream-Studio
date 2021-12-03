/* Start Header**********************************************************************************/
/*
@file    AISystem.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu		100%
@date    29/10/2021
\brief
#include "Engine/Header/AI/AISystem.hpp"
This file contain the definition of AISystem


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

//#include "Engine/Header/AI/AISystem.hpp"
//#include "Engine/Header/Debug Tools/Profiler.hpp"
//
//#include "Engine/Header/ECS/System/GraphicSystem.hpp"
//#include "Engine/Header/Graphic/Graphic.hpp"
//#include "Engine/Header/Graphic/GraphicOptions.hpp"
//#include "Engine/Header/Graphic/Mesh.hpp"
//#include "Engine/Header/Graphic/Shader.hpp"
//#include "Engine/Header/Graphic/GLSLShader.hpp"
//
//#include <list>
//#include <limits>
//
////2 = full length of a single object, 0.3 for border
//#define TILE_OFFSET 2.2f
//
//namespace Engine {
//	namespace AI {
//		bool SortReaction(const Node* lhs, const Node* rhs);
//		float distance (Node* a, Node* b);
//		//Generate list of vec2 as path
//		std::list<Math::ivec2> GeneratePath(Node* endState);
//
//		void AISystem::CreateGrid(Math::ivec2 _mapSize, Math::ivec2 _tileSize) {
//			mapSize = _mapSize;
//			tileSize = _tileSize;
//
//			nodes = new Node[static_cast<size_t>(mapSize.x) * static_cast<size_t>(mapSize.y)];
//			
//			for (int x = 0; x < mapSize.x; x++) {
//				for (int y = 0; y < mapSize.y; y++) {
//					nodes[y * mapSize.x + x].pos.x = x;
//					nodes[y * mapSize.x + x].pos.y = y;
//					nodes[y * mapSize.x + x].obstacle = true;
//					nodes[y * mapSize.x + x].parent = nullptr;
//					nodes[y * mapSize.x + x].visited = false;
//				}
//			}
//
//			for (int x = 0; x < mapSize.x; x++) {
//				for (int y = 0; y < mapSize.y; y++) {
//					//Right
//					if (x < mapSize.x - 1)
//						nodes[y * mapSize.x + x].neighbours.push_back(&nodes[(y + 0) * mapSize.x + (x + 1)]);
//					//Left
//					if (x > 0)
//						nodes[y * mapSize.x + x].neighbours.push_back(&nodes[(y + 0) * mapSize.x + (x - 1)]);
//					
//					//Top
//					if (y < mapSize.y - 1)
//						nodes[y * mapSize.x + x].neighbours.push_back(&nodes[(y + 1) * mapSize.x + (x + 0)]);
//					//Bottom
//					if (y > 0)
//						nodes[y * mapSize.x + x].neighbours.push_back(&nodes[(y - 1) * mapSize.x + (x + 0)]);
//				}
//			}
//
//			created = true;
//		}
//
//		void AISystem::AStar_Algorithm(Node* nodeStart, Node* nodeEnd) {
//			for (int x = 0; x < mapSize.x; x++) {
//				for (int y = 0; y < mapSize.y; y++) {
//					nodes[y * mapSize.x + x].globalGoal = std::numeric_limits<float>::max();
//					nodes[y * mapSize.x + x].localGoal = std::numeric_limits<float>::max();
//					nodes[y * mapSize.x + x].parent = nullptr;
//					nodes[y * mapSize.x + x].visited = false;
//				}
//			}
//
//			Node* currentNode = nodeStart;
//			nodeStart->localGoal = 0.0f;
//			nodeStart->globalGoal = distance(nodeStart, nodeEnd);
//
//			std::list<Node*> listOfUntestedNodes;
//			listOfUntestedNodes.push_back(nodeStart);
//
//			while (!listOfUntestedNodes.empty()) {
//				//Sort based on globalGoal(how well the line is)
//				listOfUntestedNodes.sort(SortReaction);
//			
//				//If visted, remove
//				while (!listOfUntestedNodes.empty() && listOfUntestedNodes.front()->visited)
//					listOfUntestedNodes.pop_front();
//
//				if (listOfUntestedNodes.empty())
//					break;
//
//				currentNode = listOfUntestedNodes.front();
//				currentNode->visited = true;
//
//				for (auto neighbour : currentNode->neighbours) {
//					auto& nb = *neighbour;
//					if (!nb.visited && !nb.obstacle)
//						listOfUntestedNodes.push_back(neighbour);
//
//					float possibleLocalGoal = currentNode->localGoal + distance(currentNode, neighbour);
//					if (possibleLocalGoal < nb.localGoal) {
//						nb.parent = currentNode;
//						nb.localGoal = possibleLocalGoal;
//
//						nb.globalGoal = nb.localGoal + distance(neighbour, nodeEnd);
//					}
//				}
//			}
//
//			GeneratePath(nodeEnd);
//		}
//
//		
//
//		void AISystem::Render(Math::mat3 camMatrix, Graphic::FrameBuffer* _fbo) {
//			PROFILER_START("Rendering");
//			return;
//
//			GLboolean gameDraw;
//			if (!_fbo)
//				gameDraw = GL_TRUE;
//			else
//				gameDraw = GL_FALSE;
//
//			//GraphicImplementation::BindFramebuffer();
//			if (gameDraw)
//				GraphicSystem::GetInstance().GetFrameBuffer().Bind();
//			else
//				_fbo->Bind();
//
//			// Load shader program
//			const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::Default].GetHandle();
//			GraphicImplementation::UseShaderHandle(shd_ref_handle);
//
//			GraphicImplementation::Renderer::BeginBatch(!gameDraw);
//
//			for (int x = 0; x < mapSize.x; x++) {
//				for (int y = 0; y < mapSize.y; y++) {
//					GraphicImplementation::Renderer::DrawQuad(
//						Math::vec2 { static_cast<float>(x) * tileSize.x * TILE_OFFSET,
//									 static_cast<float>(y) * tileSize.y * TILE_OFFSET },
//						Math::vec2{ static_cast<float>(tileSize.x), static_cast<float>(tileSize.y) }, 
//						0, 0);
//				}
//			}
//
//			for (int x = 0; x < mapSize.x; x++) {
//				for (int y = 0; y < mapSize.y; y++) {
//					for (auto n : nodes[y * mapSize.x + x].neighbours) {
//						const auto& nPos = n->pos;
//						const auto& xPos = ((static_cast<float>(x + nPos.x) / 2) * tileSize.x * TILE_OFFSET);
//						const auto& yPos = ((static_cast<float>(y + nPos.y) / 2) * tileSize.y * TILE_OFFSET);
//						GraphicImplementation::Renderer::DrawQuad(
//							Math::vec2{ xPos, yPos },
//							Math::vec2{ static_cast<float>(tileSize.x)/2, static_cast<float>(tileSize.y)/2 },
//							0, 0);
//					}
//				}
//			}
//
//
//			glEnable(GL_BLEND);
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//			//GLSLShader::SetUniform("uCamMatrix", Math::mat3{}, shd_ref_handle);
//			GLSLShader::SetUniform("uCamMatrix", camMatrix, shd_ref_handle);
//
//			GraphicImplementation::Renderer::EndBatch(!gameDraw);
//			GraphicImplementation::Renderer::Flush(!gameDraw);
//
//			// unload shader program
//			GraphicImplementation::UnUseShaderHandle();
//
//			if (gameDraw)
//				GraphicSystem::GetInstance().GetFrameBuffer().Unbind();
//			else
//				_fbo->Unbind();
//		}
//
//		void AISystem::SetRender() { render = true; }
//		void AISystem::Reset() { render = false; created = false; }
//
//		bool SortReaction(const Node* lhs, const Node* rhs) {
//			return lhs->globalGoal < rhs->globalGoal;
//		}
//
//		float distance(Node* a, Node* b) {
//			const auto& aPos = a->pos;
//			const auto& bPos = b->pos;
//			return sqrtf(static_cast<float>((aPos.x - bPos.x) * (aPos.x - bPos.x) + (aPos.y - bPos.y) * (aPos.y - bPos.y)));
//		};
//
//		std::list<Math::ivec2> GeneratePath(Node* endState) {
//			std::list<Math::ivec2> path{ };
//			Node* p = endState;
//			if (p == nullptr) return path;
//			while (p->parent != nullptr) {
//				path.push_front(Math::ivec2{ p->x, p->y });
//				p = p->parent;
//			}
//			return path;
//		}
//	}
//}