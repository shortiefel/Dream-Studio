/* Start Header**********************************************************************************/
/*
@file    GameState.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu		100%
@date    16/09/2021
\brief
This file has the function declaration of GameState


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/


#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Engine/Header/Singleton/Singleton.hpp"

namespace Engine {
	class GameState : public Singleton<GameState> {
	public:
		bool GetPlaying() const;
		void SetPlaying(bool playState);

		bool GetPause() const;
		void SetPause(bool t);
		
	private:
		bool playing = false;
		bool pause = false;

		SINGLETON_SETUP(GameState);
	};
};

#endif