/* Start Header**********************************************************************************/
/*
@file    Timer.cpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    07/10/2021
\brief
This file contains Timer definition


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#include "Engine/Header/Time/Timer.hpp"

namespace Engine {
    /*template <typename FnCallBack>
    Timer<FnCallBack>:: ~Timer() {
        if (!stopped)
            Stop();
    }*/

    /*template <typename FnCallBack>
    void Timer<FnCallBack>::Stop() {
        auto endTime = std::chrono::high_resolution_clock::now();

        long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(startTime).time_since_epoch().count();
        long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(endTime).time_since_epoch().count();
   
        float duration = (end - start) * 0.001f;

        stopped = true;

        std::cout << name << ": " << duration << " ms" << std::endl;
   }*/
}