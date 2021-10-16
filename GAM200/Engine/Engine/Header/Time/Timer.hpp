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

//#include <chrono>
#include <iostream>
#include "Engine/Header/pch.hpp"

#define FPS_Interval .5f

namespace Engine {
    template <typename FnCallBack>
    class Timer {
    public:
        Timer(const char* _name, FnCallBack&& _fnCallBack);
        ~Timer();

    private:
        const char* name;
        bool stopped;
        FnCallBack fnCallBack;
        double startTime;

        void Stop();
    };

    template <typename FnCallBack>
    Timer<FnCallBack>::Timer(const char* _name, FnCallBack&& _fnCallBack) :
        name{ _name }, fnCallBack{ _fnCallBack }, stopped{ false } {
        startTime = glfwGetTime();
    }

    template <typename FnCallBack>
    Timer<FnCallBack>::~Timer() {
        if (!stopped)
            Stop();
    }

    template <typename FnCallBack>
    void Timer<FnCallBack>::Stop() {
        double time = (glfwGetTime() - startTime) * 1000;

        stopped = true;

        //std::cout << name << ": " << time << "\n";
        fnCallBack({ name, time });
    }
}

#endif