
#include <stdexcept>

#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"

namespace Engine {

	FMOD::Sound* SoundComponent::GetSound(const std::string& _path)
	{
		auto it = _soundMap.find(_path);
		if (it == _soundMap.end())
		{
			FMOD_MODE eMode = FMOD_DEFAULT;
			eMode |= FMOD_LOOP_OFF;
			FMOD::Sound* pSound = nullptr;

			if (!System->createSound(_path.c_str(), eMode, nullptr, &pSound))
				throw std::runtime_error("FMOD: Unable to create sound" + _path);

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

		if (!it->second->setMode(eMode))
			return;
	}


}