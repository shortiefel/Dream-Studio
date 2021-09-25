/* Start Header**********************************************************************************/
/*
@file    Singleton.hpp
@author  Ow Jian Wen	jianwen.o@digipen.edu
@date    25/09/2021
\brief
This file contains Singleton template
include: #include "Engine/Header/Singleton/Singleton.hpp"


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef SINGLETON_HPP
#define SINGLETON_HPP

//Place in Private
//Creates default constructor, destructor and become friend with Singleton
#define SINGLETON_SETUP(type)\
type() {}\
~type() {}\
friend class Singleton<type>;

namespace Engine {
	template <typename T>
	class Singleton {
	public:
		static T& GetInstance() {
			static T instance;
			return instance;
		}


		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;

	protected:
		Singleton() {};
		~Singleton() {};
	};
}

#endif