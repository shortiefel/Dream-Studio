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
	enum class SoundGrp {
		MASTER = 0,
		MUSIC,
		SFX
	};

	class DSerializer;
	class SSerializer;

	struct SoundComponent : public IComponent {

		SoundComponent(Entity_id _ID = DEFAULT_ENTITY_ID, std::string _filepath = "Assets\\Sound\\sampleSound.wav", std::string _soundName = "sampleSound",
			bool _isSound = false, bool _isActive = false, bool _loop = false, float _vol = 1.0f, SoundGrp _soundType = SoundGrp::MASTER, bool _isBGMMuted = false, bool _isSFXMuted = false);
		~SoundComponent();

		SoundComponent& Deserialize(const DSerializer& _serializer);
		void Serialize(const SSerializer& _serializer);

		/**
		*		VOLUME
		*/
		float GetVolume(float _vol);
		float SetVolume(float _vol);


		std::string filepath;
		std::string soundName;

		float volume;
		bool isSound, loop, isMute;
		bool isActive = true;

		SoundGrp soundType;

		bool isPlaying = false;
		int channelID = -1;

		bool isBGMMuted, isSFXMuted;
		bool isIncrease = true, isDecrease = true;
	};

}
#endif