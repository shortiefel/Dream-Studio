#ifndef SOUND_COMPONENT_H
#define SOUND_COMPONENT_H

#include <fmod/fmod.hpp>
#include <map>
#include "Engine/Header/ECS/Component/IComponent.hpp"

namespace Engine {

	typedef  std::map<std::string, FMOD::Sound*> SoundMap;
	typedef std::map<int, FMOD::Channel*> ChannelMap;

	struct SoundComponent : public IComponent {
		

		SoundComponent();
		~SoundComponent();
		FMOD::Sound* GetSound(const std::string& _path);
		void SetLoop(int channelID, bool _loop);
		

		/**
		*		VOLUME
		*/
	/*	float VolumeDecimal(float _vol);
		float DecimalVolume(float _vol);*/

		static SoundMap _soundMap;
		static FMOD::System* System;
		static ChannelMap channelMap;

		std::string filepath = "";
		//std::string soundName = "";

		//float volume;
		bool isSound;
		bool isActive = true;
		int ChannelID;
		bool loop;
			


	};

}


#endif