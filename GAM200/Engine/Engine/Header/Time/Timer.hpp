/* Start Header**********************************************************************************/
/*
@file    Timer.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    07/10/2021
\brief
This file contains Timer declaration


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>

#define FPS_Interval .5f
//#define START_TIME(name, func) Timer timer##__LINE__(name, func);

namespace Engine {
    template <typename FnCallBack>
    class Timer {
    public:
        Timer(const char* _name, FnCallBack&& _fnCallBack) :
            name{ _name }, fnCallBack{ _fnCallBack }, stopped{ false } {
            startTime = std::chrono::high_resolution_clock::now();
        }
        ~Timer() {
            if (!stopped)
                Stop();
        }

    private:
        const char* name;
        bool stopped;
        FnCallBack fnCallBack;
        std::chrono::time_point<std::chrono::steady_clock> startTime;

        void Stop() {
            auto endTime = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

            float time = (end - start) * 0.001f;

            stopped = true;

            fnCallBack({ name, time });
            //std::cout << name << ": " << 1/(duration * 0.001f) << " fps" << std::endl;
        }
    };
}

#endif