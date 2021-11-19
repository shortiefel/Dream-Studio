#ifndef SOUND_COMPONENT_H
#define SOUND_COMPONENT_H

#include <fmod/fmod.hpp>
#include <map>
#include "Engine/Header/ECS/Component/IComponent.hpp"


#include "Engine/Header/pch.hpp"
#include "Engine/Header/Serialize/DSerializer.hpp"
#include "Engine/Header/Serialize/SSerializer.hpp"

namespace Engine {

	typedef  std::map<std::string, FMOD::Sound*> SoundMap;
	typedef std::map<int, FMOD::Channel*> ChannelMap;

	struct SoundComponent : public IComponent {
		

		SoundComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "Assets\\Sound\\sampleSound", bool _isSound = false, bool _isActive = false, int channelID = 0, bool _loop = false);
		~SoundComponent();
		static FMOD::Sound* GetSound(const std::string& _path);
		void SetLoop(int channelID, bool _loop);
		bool IsPlaying(int channelID);
		

		/**
		*		VOLUME
		*/
	/*	float VolumeDecimal(float _vol);
		float DecimalVolume(float _vol);*/

		static SoundMap _soundMap;
		static FMOD::System* System;
		static ChannelMap channelMap;
		static FMOD::ChannelGroup* MasterGroup;
		static FMOD::ChannelGroup* MusicGroup;

		std::string filepath = "";
		std::string soundName = "";

		//float volume;
		bool isSound;
		bool isActive = true;
		int ChannelID;
		bool loop;
			


	};

}


#endif