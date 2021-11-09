/* Start Header**********************************************************************************/
/*
@file    SoundObject.cpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
@date    09/11/2021
@brief

This file contains the functions to play various sounds in the editor, it will be loaded from file path to editor
and saved as wav files.


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/ECS/Component/Sound/SoundObject.hpp"
#include <fstream>

#define FILE_CREATION(path, type)\
FILE* fp;\
fopen_s(&fp, path, type);\
if (!fp) {\
	LOG_WARNING("File is not found");\
	return;\
}

#define TO_FULL_SOUND(name) ("Assets/Audio/" + name + ".wav")

namespace Engine {

	void SoundObject::PlayAudio(std::string filename) 
	{
		if (loop)
		{
			if (SoundComponent::ChannelID)
				filename;
				SoundComponent::PauseEnd(SoundComponent::ChannelID);
		}
		else
			SoundComponent::EPlaySound(filename, 0.5f, false);
	}

	void SoundObject::StopAudio(std::string filename)
	{
		if (!loop)
			return;
		if (SoundComponent::ChannelID)
			filename;
		SoundComponent::StopSound(SoundComponent::ChannelID);
	}

	void SoundObject::MuteAudio(std::string filename)
	{
		if (!loop)
			return;
		if (SoundComponent::ChannelID)
			filename;
		SoundComponent::SetVolume(0.f);
	}

	void SoundObject::UnmuteAudio(std::string filename)
	{

		if (!loop) return;
		if (SoundComponent::ChannelID)
			filename;
		SoundComponent::SetVolume(0.5f);
	}

	void SoundObject::SetAudioVolume(std::string filename, float vol)
	{
		SoundComponent::volume = vol;
		if (!loop) 
			return;
		if (SoundComponent::ChannelID)
			filename;
		SoundComponent::SetVolume(vol);

	}

	void SoundObject::SetAudioLoop(std::string filename, bool isActive)
	{
		if (loop != isActive)
			return;
		if (!loop)
			SoundComponent::SetLoop(SoundComponent::ChannelID, false);
		else
		{
			SoundComponent::ChannelID = SoundComponent::EPlaySound(filename, 0.5f, true);
			SoundComponent::SetLoop(SoundComponent::ChannelID, false);
		}

	}
}