#include "Engine/Header/ECS/System/SoundSystem.hpp"

#include <stdexcept>


namespace Engine
{
	std::map<std::string, FMOD::Sound*> SoundComponent::_soundMap;
	FMOD::System* SoundComponent::System = nullptr;
	
	void SoundSystem::SoundInit()
	{
		if (!FMOD::System_Create(&SoundComponent::System))
			throw std::runtime_error("FMOD: Failed to create system object");

		if (!SoundComponent::System->init(512, FMOD_INIT_NORMAL, nullptr))
			throw std::runtime_error("FMOD: Failed to initialise system object");

		if (!SoundComponent::System->getMasterChannelGroup(&MasterGroup))
			throw std::runtime_error("FMOD: Failed to get Master Channel Group");

		if (!SoundComponent::System->createChannelGroup("Music", &MusicGroup))
			throw std::runtime_error("FMOD: Failed to create Music Channel Group");

		//to set volume in future

	}

	void SoundSystem::SoundUpdate()
	{
		for (auto it = SoundComponent::channelMap.begin(); it != SoundComponent::channelMap.end(); ++it)
		{
			bool bIsPlaying = false;
			it->second->isPlaying(&bIsPlaying);
		}

		if(!SoundComponent::System->update())
			throw std::runtime_error("FMOD: Failed to Update System");

	//	System->createSound("C:/Users/tanwe/OneDrive/Desktop/GAM200/GAM200/Editor/Assets/Audio/sampleSound.wav", FMOD_LOOP_NORMAL, 0, &test);
		//System->playSound(test,0 , false, 0);

	}



	void SoundSystem::SoundRelease()
	{
		std::map<std::string, FMOD::Sound*>::iterator soundit;
		for (soundit = SoundComponent::_soundMap.begin(); soundit != SoundComponent::_soundMap.end(); ++soundit)
		{
			soundit->second->release();
		}

		SoundComponent::_soundMap.clear();
		SoundComponent::channelMap.clear();
		MusicGroup->release();
		MasterGroup->release();
		SoundComponent::System->release();
	}

}