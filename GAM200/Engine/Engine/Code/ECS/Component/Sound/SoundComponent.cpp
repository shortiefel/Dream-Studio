/* Start Header**********************************************************************************/
/*
@file			SoundComponent.cpp
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
#include <stdexcept>

#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"

namespace Engine {

	std::string _path;
	int channelID;
	std::string SoundComponent::filepath = _path;
	int SoundComponent::ChannelID = channelID;
	float _vol;
	float SoundComponent::volume = _vol;

	SoundComponent::SoundComponent(Entity_id _ID, const std::string g_path, bool g_isSound, bool g_isActive, bool g_loop, bool g_pause, SoundGrp g_SG) :
		IComponent{ _ID }, isSound{ g_isSound }, isActive{ g_isActive }, loop{ g_loop }, Pause{ g_pause }, SG{ g_SG } {

		SoundComponent::GetSound(g_path);
	}
	SoundComponent::~SoundComponent() {

		
	}


	FMOD::Sound* SoundComponent::GetSound(const std::string& g_path)
	{
		auto it = _soundMap.find(g_path);
		if (it == _soundMap.end())
		{
			FMOD_MODE eMode = FMOD_DEFAULT;
			eMode |= FMOD_LOOP_OFF;
			FMOD::Sound* pSound = nullptr;

			System->createSound(g_path.c_str(), eMode, nullptr, &pSound);
				//throw std::runtime_error("FMOD: Unable to create sound" + _path);

			if (pSound)
				_soundMap[g_path] = pSound;

			return pSound;
		}

		return it->second;
	}

	void SoundComponent::SetLoop(int g_channelID, bool g_loop)
	{
		auto it = channelMap.find(g_channelID);
		if (it == channelMap.end())
		{
			return;
		}
		FMOD_MODE eMode = FMOD_LOOP_NORMAL;
		eMode |= g_loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

		if (it->second->setMode(eMode))
			return;
	}
	
	bool SoundComponent::IsPlaying(int g_channelID)
	{
		auto it = channelMap.find(g_channelID);
		if (it == channelMap.end())
		{
			return false;
		}
		bool bIsPlaying = false;
		it->second->isPlaying(&bIsPlaying);
		return bIsPlaying;
	}
	
	/**
	*		VOLUMES
	*		--- LOUD = 100.f ->1.f
	*		--- NORMAL = 50.f -> 0.5f
	*		--- SOFT = 20.f ->0.2f
	*/
	float SoundComponent::VolumeDecimal(float g_vol)
	{
		if (g_vol < 20.f)
			g_vol = 20.f;
		else if (g_vol >= 20.f && g_vol <= 100.f)
			g_vol = 50.f;
		else if (g_vol > 100.f)
			g_vol = 100.f;

		return g_vol / 100.f;
			
	}

	float SoundComponent::DecimalVolume(float g_vol)
	{
		return g_vol * 100.f;
	}

	SoundComponent& SoundComponent::Deserialize(const DSerializer& _serializer)
	{

		//isSound{ _isSound }, isActive{ _isActive }, loop{ _loop }, Pause{ _pause }

		SG = SoundGrp(_serializer.GetValue<int>("SoundGrpType"));
		isActive = _serializer.GetValue<bool>("IsActive");
		loop = _serializer.GetValue<bool>("IsLoop");
		Pause = _serializer.GetValue<bool>("IsPause");
		SoundComponent::GetSound(std::move(_serializer.GetValue<std::string>("filepath")));
		volume = _serializer.GetValue<float>("volume");
		isSound = _serializer.GetValue<bool>("isSound");

		return *this;
	}

	void SoundComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("SoundGrpType", (int)SG);
		_serializer.SetValue("IsActive", isActive);
		_serializer.SetValue("IsLoop", loop);
		_serializer.SetValue("IsPause", Pause);
		_serializer.SetValue("filepath", filepath);
		_serializer.SetValue("volume", volume);
		_serializer.SetValue("isSound", isSound);
	}

}