/* Start Header**********************************************************************************/
/*
@file    GameSceneSerializer.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
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

namespace Engine {
	class GameSceneSerializer {
	public:
		static void SerializeSetting();
		static void DeserializeSetting();

		//From scene to a file
		static void SerializeScene(std::string filename);
		//From file to a scene
		static void DeserializeScene(std::string filename);
	};
}
#endif