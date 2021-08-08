#include "Engine/Header/DeltaTime/DeltaTime.hpp"

namespace Engine {
	float DeltaTime::m_time = 0.f, DeltaTime::fps = 0;

	void DeltaTime::UpdateDeltaTime(float current_time, float last_time) {
		static float new_wait_time = current_time;
		m_time = current_time - last_time;

		//Update fps by FPS_Interval
		if (current_time - new_wait_time > FPS_Interval) {
			new_wait_time = current_time;
			fps = 1 / m_time;
		}
	}
}