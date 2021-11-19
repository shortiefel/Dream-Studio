#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H


#include "Engine/Header/pch.hpp"
#include "Engine/Header/Singleton/Singleton.hpp"
#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"

#include <fmod/fmod.hpp>
#include <map>
#include <string>

namespace Engine {

	//typedef std::map<std::string  , FMOD::Sound*> SoundMap;
	//typedef std::map<int, FMOD::Channel*> ChannelMap;

	struct SoundSystem : public Singleton<SoundSystem>
	{

		/**
		*		BASICS
		*/
		static void SoundInit();
		static void SoundUpdate();
		static void SoundRelease();

		SINGLETON_SETUP(SoundSystem);

	};
}

#endif
