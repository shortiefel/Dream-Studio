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

	SoundComponent::SoundComponent(Entity_id _ID, const std::string _path, bool _isSound, bool _isActive, bool _loop, bool _pause, SoundGrp SG) :
		IComponent{ _ID }, isSound{ _isSound }, isActive{ _isActive }, loop{ _loop }, Pause{ _pause }, SG{SoundGrp::MASTER} {

		SoundComponent::GetSound(_path);
	}
	SoundComponent::~SoundComponent() {

		
	}


	FMOD::Sound* SoundComponent::GetSound(const std::string& _path)
	{
		auto it = _soundMap.find(_path);
		if (it == _soundMap.end())
		{
			FMOD_MODE eMode = FMOD_DEFAULT;
			eMode |= FMOD_LOOP_OFF;
			FMOD::Sound* pSound = nullptr;

			System->createSound(_path.c_str(), eMode, nullptr, &pSound);
				//throw std::runtime_error("FMOD: Unable to create sound" + _path);

			if (pSound)
				_soundMap[_path] = pSound;

			return pSound;
		}

		return it->second;
	}

	void SoundComponent::SetLoop(int channelID, bool _loop)
	{
		auto it = channelMap.find(channelID);
		if (it == channelMap.end())
		{
			return;
		}
		FMOD_MODE eMode = FMOD_LOOP_NORMAL;
		eMode |= _loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;

		if (it->second->setMode(eMode))
			return;
	}
	
	bool SoundComponent::IsPlaying(int channelID)
	{
		auto it = channelMap.find(channelID);
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
	float SoundComponent::VolumeDecimal(float _vol)
	{
		if (_vol < 20.f)
			_vol = 20.f;
		else if (_vol >= 20.f && _vol <= 100.f)
			_vol = 50.f;
		else if (_vol > 100.f)
			_vol = 100.f;

		return _vol / 100.f;
			
	}

	float SoundComponent::DecimalVolume(float _vol)
	{
		return _vol * 100.f;
	}

	SoundComponent& SoundComponent::Deserialize(const DSerializer& _serializer)
	{

		//isSound{ _isSound }, isActive{ _isActive }, loop{ _loop }, Pause{ _pause }

		SG = SoundGrp(_serializer.GetValue<int>("SoundGrpType"));
		isActive = _serializer.GetValue<bool>("IsActive");
		loop = _serializer.GetValue<bool>("IsLoop");
		Pause = _serializer.GetValue<bool>("IsPause");
		SoundComponent::GetSound(std::move(_serializer.GetValue<std::string>("Filepath")));
		//volume = _serialize.GetValue<float>("Volume");
		//isSound = _serialize.GetValue<bool>("Soundbool");

		return *this;
	}

	void SoundComponent::Serialize(const SSerializer& _serializer)
	{
		_serializer.SetValue("SoundGrpType", (int)SG);
		_serializer.SetValue("IsActive", isActive);
		_serializer.SetValue("IsLoop", loop);
		_serializer.SetValue("IsPause", Pause);
		_serializer.SetValue("Filepath", filepath);
	}

}