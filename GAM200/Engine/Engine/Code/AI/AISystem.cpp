/* Start Header**********************************************************************************/
/*
@file    AISystem.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

#include "Engine/Header/AI/AISystem.hpp"
#include "Engine/Header/Debug Tools/Profiler.hpp"

#include "Engine/Header/ECS/System/GraphicSystem.hpp"
#include "Engine/Header/Graphic/Graphic.hpp"
#include "Engine/Header/Graphic/GraphicOptions.hpp"
#include "Engine/Header/Graphic/Mesh.hpp"
#include "Engine/Header/Graphic/Shader.hpp"
#include "Engine/Header/Graphic/GLSLShader.hpp"

//2 = full length of a single object, 0.3 for border
#define TILE_OFFSET 2.2f

#include "Engine/Header/Management/TextureManager.hpp"
#include <string>

namespace Engine {
	namespace AI {
		unsigned int texobj_hdl;
		std::string filepath = "Assets\\Textures\\OneWayRoad.png";

		void AISystem::CreateGrid(Math::ivec2 _mapSize, Math::ivec2 _tileSize) {
			mapSize = _mapSize;
			tileSize = _tileSize;

			nodes = new Node[static_cast<size_t>(mapSize.x) * static_cast<size_t>(mapSize.y)];
			
			for (int x = 0; x < mapSize.x; x++) {
				for (int y = 0; y < mapSize.y; y++) {
					nodes[y * mapSize.x + x].pos.x = x;
					nodes[y * mapSize.x + x].pos.y = y;
					nodes[y * mapSize.x + x].obstacle = true;
					nodes[y * mapSize.x + x].parent = nullptr;
					nodes[y * mapSize.x + x].visited = false;
				}
			}

			created = true;
		}

		void AISystem::AStar_Algorithm() {
			for (int x = 0; x < mapSize.x; x++) {
				for (int y = 0; y < mapSize.y; y++) {
					nodes[y * mapSize.x + x].globalGoal;
					nodes[y * mapSize.x + x].localGoal;
					nodes[y * mapSize.x + x].parent = nullptr;
					nodes[y * mapSize.x + x].visited = false;
				}
			}
		}

		void AISystem::Render(Math::mat3 camMatrix, Graphic::FrameBuffer* _fbo) {
			PROFILER_START("Rendering");

			GLboolean gameDraw;
			if (!_fbo)
				gameDraw = GL_TRUE;
			else
				gameDraw = GL_FALSE;

			//GraphicImplementation::BindFramebuffer();
			if (gameDraw)
				GraphicSystem::GetInstance().GetFrameBuffer().Bind();
			else
				_fbo->Bind();

			// Load shader program
			const auto& shd_ref_handle = GraphicImplementation::shdrpgms[GraphicShader::DEFAULT].GetHandle();
			GraphicImplementation::UseShaderHandle(shd_ref_handle);

			GraphicImplementation::Renderer::ResetStats();
			GraphicImplementation::Renderer::BeginBatch(!gameDraw);

			for (int x = 0; x < mapSize.x; x++) {
				for (int y = 0; y < mapSize.y; y++) {
					GraphicImplementation::Renderer::DrawQuad(
						Math::vec2 { static_cast<float>(x) * tileSize.x * TILE_OFFSET,
									 static_cast<float>(y) * tileSize.y * TILE_OFFSET },
						Math::vec2{ static_cast<float>(tileSize.x), static_cast<float>(tileSize.y) }, 
						0, 0);
				}
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//GLSLShader::SetUniform("uCamMatrix", Math::mat3{}, shd_ref_handle);
			GLSLShader::SetUniform("uCamMatrix", camMatrix, shd_ref_handle);

			GraphicImplementation::Renderer::EndBatch(!gameDraw);
			GraphicImplementation::Renderer::Flush(!gameDraw);

			// unload shader program
			GraphicImplementation::UnUseShaderHandle();

			if (gameDraw)
				GraphicSystem::GetInstance().GetFrameBuffer().Unbind();
			else
				_fbo->Unbind();
		}

		void AISystem::SetRender() { render = true; }
		void AISystem::Reset() { render = false; created = false; }

	}
}