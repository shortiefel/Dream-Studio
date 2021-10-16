/* Start Header**********************************************************************************/
/*
@file    DeltaTime.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    16/10/2021
\brief
#include "Engine/Header/Time/DeltaTime.hpp"
This file contain the DeltaTime declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef DELTA_TIME
#define DELTA_TIME

#include "Engine/Header/Singleton/Singleton.hpp"

namespace Engine {
	class DeltaTime : public Singleton<DeltaTime> {
	public:
		float GetFPS() const;
		void SetFPS(float _fps);
		float GetDeltaTime() const;
		//Set current dt, add to total time and increment the loop count
		void SetDeltaTime(float _dt);

		float GetFixedDeltaTime();
	private:
		float dt = 1/60.0f;
		float fps = 60.f;

		static float totalTime;
		static int loopCount;

		SINGLETON_SETUP(DeltaTime);
	};
}

#endif