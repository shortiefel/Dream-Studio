/* Start Header**********************************************************************************/
/*
@file    GameScene.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    23/06/2021
\brief
This contain the declaration of GameScene class with its function
*/
/* End Header **********************************************************************************/

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

class GameScene {
public:
	static void Create();
	static void Destroy();
	static void Update(float dt);
};

#endif