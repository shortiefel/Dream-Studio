/* Start Header**********************************************************************************/
/*
@file    SoundComponent.hpp
@author  Tan Wei Ling Felicia	 weilingfelicia.tan@digipen.edu
@date    04/10/2021
@brief



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

typedef std::map<std::string, FMOD::Sound*> SoundMap;

namespace Engine {

	class DSerializer;
	class SSerializer;


	class SoundComponent : public IComponent {

		public:
			SoundComponent(const std::string _path, bool _isActive);
			~SoundComponent();

			void Update(float elapsed);
			void Load(const std::string& _path);
			void Stream(const std::string& _path);
			void Play(const std::string& _path);
			void LoadStream(const std::string& _path, bool _isActive);

			SoundComponent& Deserialize(const DSerializer& _serializer);
			void Serialize(const SSerializer& _serializer);

		private:
			std::string path = "";
			bool isActive;
			FMOD::System* system;
			SoundMap sounds;

	};
}


#endif // !SOUND_COMPONENT_H

