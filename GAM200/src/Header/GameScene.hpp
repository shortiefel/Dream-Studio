/* Start Header**********************************************************************************/
/*
@file    GameScene.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    23/06/2021
\brief
This contain the declaration of GameScene class with its function


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

class GameScene {
public:
	static void Create();
	static void Destroy();
	static void Play();
	static void Stop();
	static void Update(float dt);
};

#endif