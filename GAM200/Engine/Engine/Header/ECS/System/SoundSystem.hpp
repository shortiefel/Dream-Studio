#pragma once

#include <fmod/fmod.hpp>
#include <map>
#include <string>

namespace Engine {

	typedef std::map<std::string  , FMOD::Sound*> SoundMap;
	class SoundSystem {

	public:
		static void SoundInit();
		static void SoundUpdate();
		static void SoundRelease();

	private:
		static FMOD::System* System;
		static FMOD::ChannelGroup* MasterChannel;
		static 	SoundMap _SoundMap;

	};
}
