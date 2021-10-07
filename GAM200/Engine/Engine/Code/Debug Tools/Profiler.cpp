/* Start Header**********************************************************************************/
/*
@file    Profiler.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    07/10/2021
\brief
This file contain the Profiler definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Debug Tools/Profiler.hpp"
#include <iostream>

namespace Engine {
	void Profiler::DisplayProfilerResult() {
		for (const auto& result : profilerResult) {
			std::cout << result.name << ": " << result.time << std::endl;
		}

		profilerResult.clear();
	}
}