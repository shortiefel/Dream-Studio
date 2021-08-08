/* Start Header**********************************************************************************/
/*
@file    DeltaTime.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    05/07/2021
\brief
This file has class DeltaTime


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef DELTA_TIME_HPP
#define DELTA_TIME_HPP

namespace Engine {
#define FPS_Interval .5f

	class DeltaTime {
	public:
		/*DeltaTime() : m_time{ 0.f } {}
		DeltaTime(float time) : m_time{ time }, fps{ 1 / m_time } {}*/

		inline static float GetSec() { return m_time; }
		inline static float GetFPS() { return fps; }

		static void UpdateDeltaTime(float current_time, float last_time);

	private:
		static float m_time, fps;
	};
}

#endif