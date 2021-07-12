/* Start Header**********************************************************************************/
/*
@file    TimeClock.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    05/07/2021
\brief
This file has class TimeClock


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

	class TimeClock {
	public:
		TimeClock() : m_time{ 0.f } {}
		TimeClock(float time) : m_time{ time }, fps{ static_cast<int>(1 / m_time) } {}

		inline float GetSec() const { return m_time; }
		inline float GetMilliSec() const { return m_time * 1000.f; }
		inline int GetFPS() const { return fps; }

		void UpdateTimeClock(float current_time, float last_time) {
			static float new_wait_time = current_time;
			m_time = current_time - last_time;

			//Update fps by FPS_Interval
			if (current_time - new_wait_time > FPS_Interval) {
				new_wait_time = current_time;
				fps = static_cast<int>(1 / m_time);
			}
		}

	private:
		float m_time = 0.f;
		int fps = 0;
	};
}

#endif