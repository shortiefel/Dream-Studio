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

namespace Engine {
    class Timer {
        public:
        Timer(const char* _name);
        ~Timer();
        private:
        const char* name;
        bool stopped;

        void Stop();
    }
}

#endif