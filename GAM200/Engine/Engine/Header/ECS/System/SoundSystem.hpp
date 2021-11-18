#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H


#include "Engine/Header/pch.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"

#include <fmod/fmod.hpp>
#include <map>
#include <string>

namespace Engine {

	typedef std::map<std::string  , FMOD::Sound*> SoundMap;

	class SoundSystem : public Singleton<SoundSystem>
	{

	public:
		static void SoundInit();
		static void SoundUpdate();
		static void SoundRelease();

	private:
		static FMOD::System* System;
		static FMOD::ChannelGroup* MasterChannel;
		static 	SoundMap _SoundMap;

		SINGLETON_SETUP(SoundSystem);

	};
}

#endif
