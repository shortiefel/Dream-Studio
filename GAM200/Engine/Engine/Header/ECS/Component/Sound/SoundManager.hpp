/* Start Header**********************************************************************************/
/*
@file    SoundManager.hpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
@date    08/11/2021
@brief



Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include <string>
#include <map>
#include <fmod/fmod.hpp>

namespace Engine {

	class SoundManager
	{
		public:
			SoundManager();
			~SoundManager();

			void Update(float elapsed);
			void LoadSFX(const std::string& path);
			void LoadSong(const std::string& path);

			void PlaySFX(const std::string& path, float minPitch, float maxPitch);
			void PlaySong(const std::string& path);

			void StopSFX();
			void StopSongs();

			void SetMasterVolume(float volume);
			void SetSFXsVolume(float volume);
			void SetSongsVolume(float volume);
		
	private:
			typedef std::map<std::string, FMOD::Sound*> SoundMap;
			enum Category { CATEGORY_SFX, CATEGORY_SONG, CATEGORY_COUNT };

			void Load(Category type, const std::string& path);

			FMOD::System* system;
			FMOD::ChannelGroup* master;
			FMOD::ChannelGroup* groups[CATEGORY_COUNT];
			SoundMap sounds[CATEGORY_COUNT];
			FMOD_MODE modes[CATEGORY_COUNT];

			FMOD::Channel* currentSong;
			std::string currentSongPath;
			std::string nextSongPath;

			enum FadeState { FADE_NONE, FADE_IN, FADE_OUT };
			FadeState fade;
	};

}