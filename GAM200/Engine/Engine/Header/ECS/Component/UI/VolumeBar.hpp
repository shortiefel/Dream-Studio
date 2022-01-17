#ifndef VOLUME_BAR_HPP
#define VOLUME_BAR_HPP

#include "Engine/Header/ECS/Component/IComponent.hpp"
#include "Engine/Header/Math/MathLib.hpp"
#include "Engine/Header/ECS/Component/UI/UIComponent.hpp"
#include "Engine/Header/ECS/Component/Sound/SoundComponent.hpp"

namespace Engine
{
	struct VolumeBar : public UIComponent
	{
		static constexpr float maxX = 100.f;
		static constexpr float minX = -100.f;

		VolumeBar(DreamMath::vec2 currentVolBar);
		~VolumeBar();

		void InitVolumeBar();

		UIComponent* increaseButton;
		UIComponent* decreaseButton;




	};

}

#endif
