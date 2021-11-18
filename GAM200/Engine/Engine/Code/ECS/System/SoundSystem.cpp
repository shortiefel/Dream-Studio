#include "../../../../Engine/Header/ECS/System/SoundSystem.hpp"




namespace Engine
{
	std::map<std::string, FMOD::Sound*> SoundSystem::_SoundMap;
	FMOD::System* SoundSystem::System = nullptr;
	
	void SoundSystem::SoundInit()
	{
		FMOD::System_Create(&System);
		System->init(100, FMOD_INIT_NORMAL, 0);
		SoundSystem::SoundUpdate();
		System->update();
	}

	void SoundSystem::SoundUpdate()
	{
		FMOD::Sound* test;

		System->createSound("C:/Users/tanwe/OneDrive/Desktop/GAM200/GAM200/Editor/Assets/Audio/sampleSound.wav", FMOD_LOOP_NORMAL, 0, &test);
		System->playSound(test,0 , false, 0);

	}

	void SoundSystem::SoundRelease()
	{
		SoundMap::iterator iter;
		for (iter = _SoundMap.begin(); iter != _SoundMap.end(); ++iter)
			iter->second->release();
		_SoundMap.clear();

		System->release();
		System = 0;
	}

}