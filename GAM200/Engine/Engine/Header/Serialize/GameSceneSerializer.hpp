/* Start Header**********************************************************************************/
/*
@file    GameSceneSerializer.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu	100%
@date    15/07/2021
\brief
This file contain the GameSceneSerializer declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GAMESCENE_SERIALIZER_HPP
#define GAMESCENE_SERIALIZER_HPP

#include <string>
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/ECS/ECSGlobal.hpp"

namespace Engine {
	class GameSceneSerializer {
	public:
		static void SerializeSetting();
		static void DeserializeSetting();

		//From scene to a file
		static void SerializeScene(std::string filename);
		//From file to a scene
		static void DeserializeScene(std::string filename);
		//From scene to prefab
		static void SerializePrefab(std::string filename, Entity_id entity_id);

		static void ClearDeserializePool();
		//From prefab to scene
		static void DeserializePrefab(std::string filename, unsigned int* id = nullptr, Math::vec2 position = Math::vec2{}, float angle = 0.f, int layer = 2);
		static void RefreshPrefab(std::string filename, Entity_id id);
	};
}
#endif