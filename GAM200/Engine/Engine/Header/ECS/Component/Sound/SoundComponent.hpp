/* Start Header**********************************************************************************/
/*
@file    SoundComponent.hpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
@date    04/10/2021
@brief

This file contains the declaration function for sound component with FMOD


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SOUND_COMPONENT_H
#define SOUND_COMPONENT_H

#include <fmod/fmod.hpp>
#include <string>
#include <map>

#include "Engine/Header/ECS/Component/IComponent.hpp"



namespace Engine {

	class DSerializer;
	class SSerializer;


	class SoundComponent : public IComponent {

		public:
			static float VolumeToDecibels(float volume);
			static float DecibelsToVolume(float volume);
			static float GetVolume(int ChannelID);


			static void Init();
			static void ReleaseAll();
			static int EPlaySound(const std::string& file, float volume,  bool paused);
			static void Pause(int ChannelID);
			static void PauseEnd(int ChannelID);
			static void StopSound(int ChannelID);
			static bool IsPlaying(int ChannelID);
			static void SetVolume(int ChannelID, float volume);
			static void ChangeVolume(int ChannelID, float volume);
			static void SetVolume(float volume);
			static void SetLoop(int ChannelID, bool isLoop);
			static FMOD::Sound* GetSound(const std::string& file);
			static bool Update();

			static FMOD::System* SystemCore;
			static FMOD::SoundGroup* SoundGroup;
			static FMOD::Channel* Channel;
			static FMOD::ChannelGroup* MasterGroup;
			static FMOD::ChannelGroup* MusicGroup;
			static std::map<std::string, FMOD::Sound*> SoundMap;
			static std::map<int, FMOD::Channel*> ChannelMap;

			static float volume;
			std::string file = "";
			static int ChannelID;

			static float MinDecibels;
			static float MaxDeciibels;

	};
}


#endif // !SOUND_COMPONENT_H

