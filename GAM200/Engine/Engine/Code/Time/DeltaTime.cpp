/* Start Header**********************************************************************************/
/*
@file    DeltaTime.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    16/10/2021
\brief
This file contain the DeltaTime definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Time/DeltaTime.hpp"

namespace Engine {
	float DeltaTime::totalTime = 0.f;
	int DeltaTime::loopCount = 0;

	float DeltaTime::GetFPS() const { return fps; }
	void DeltaTime::SetFPS(float _fps) { fps = _fps; }
	float DeltaTime::GetDeltaTime() const { return dt; }
	void DeltaTime::SetDeltaTime(float _dt) { 
		dt = _dt; 

		totalTime += _dt;
		++loopCount;
	}

	float DeltaTime::GetFixedDeltaTime() { return totalTime/loopCount; }
}