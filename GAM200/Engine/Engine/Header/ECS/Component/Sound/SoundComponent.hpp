/* Start Header**********************************************************************************/
/*
@file			SoundComponent.hpp
@author	Tan Wei Ling Felicia	weilingfelicia.tan@digipen.edu	100%
@date		15/11/2021
\brief
This file contain the Components needed for sound

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

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

	enum class SoundGrp {
		MASTER,
		MUSIC,
		SFX
	};

	class DSerializer;
	class SSerializer;

	struct SoundComponent : public IComponent {
		

		SoundComponent(Entity_id _ID = DEFAULT_ENTITY_ID, const std::string _path = "Assets\\Sound\\sampleSound",
			bool _isSound = false, bool _isActive = false, bool _loop = false, bool _pause = false, SoundGrp SG = SoundGrp::MASTER);
		~SoundComponent();
		static FMOD::Sound* GetSound(const std::string& _path);
		void SetLoop(int channelID, bool _loop);
		static bool IsPlaying(int channelID);
		

		SoundComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		/**
		*		VOLUME
		*/
		static float VolumeDecimal(float _vol);
		static float DecimalVolume(float _vol);


		/**
		*		FMOD RELATED
		*/
		static SoundMap _soundMap;
		static FMOD::System* System;
		static ChannelMap channelMap;
		static FMOD::ChannelGroup * MasterGroup;
		static FMOD::ChannelGroup* MusicGroup;
		static FMOD::ChannelGroup* SFXGroup;


		SoundGrp SG;
		static std::string filepath;
		std::string soundName = "";

		static float volume;
		bool isSound, loop, Pause;
		bool isActive = true;
		static int ChannelID;


	};

}
#endif