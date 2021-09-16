#include "Engine/Header/Management/GameState.hpp"

namespace Engine {
	bool GameState::playing = false;

	bool GameState::GetPlaying() { return playing; }
	void GameState::SetPlaying(bool playState) { playing = playState; }
}