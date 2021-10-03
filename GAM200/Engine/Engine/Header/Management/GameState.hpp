/* Start Header**********************************************************************************/
/*
@file    GameState.hpp
@authors	Goh See Yong Denise		g.seeyongdenise@digipen.edu
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

namespace Engine {
	class GameState {
	public:
		static bool GetPlaying();
		static void SetPlaying(bool playState);
	private:
		static bool playing;
	};
};

#endif