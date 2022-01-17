#include "Engine/Header/ECS/Component/UI/VolumeBar.hpp"
#include "Engine/Header/ECS/Component/ComponentManager.hpp"

namespace Engine
{
	VolumeBar::VolumeBar(DreamMath::vec2 currentVolBar)
	{
		/*SoundComponent* soundCom;
		Math::vec2 volMaster;
		if (increaseButton->isActive )
			currentVolBar += soundCom->GetVolume(volMaster.x);
		if (decreaseButton->isActive)
			currentVolBar -= soundCom->GetVolume(volMaster.x);*/
		SoundComponent* soundCom;
		soundCom->GetVolume(currentVolBar.x);
		InitVolumeBar();
		

	}

	VolumeBar::~VolumeBar()
	{

	}

	void VolumeBar::InitVolumeBar()
	{


		//increaseButton->colour(0, 0, 0, 1);
		

	}
}