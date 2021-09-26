/* Start Header**********************************************************************************/
/*
@file    GameState.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    16/09/2021
\brief
This file has the function definition of GameState


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Management/GameState.hpp"

namespace Engine {
	bool GameState::playing = false;

	bool GameState::GetPlaying() { return playing; }
	void GameState::SetPlaying(bool playState) { playing = playState; }
}