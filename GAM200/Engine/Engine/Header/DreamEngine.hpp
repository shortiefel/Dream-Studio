/* Start Header**********************************************************************************/
/*
@file    DreamEngine.hpp
@author  Ow Jian Wen	jianwen123321@hotmail.com
@date    05/07/2021
\brief
This file has the included header for core engine use
This file is specifically for application using Dream Engine API


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **********************************************************************************/

#ifndef DREAM_ENGINE_HPP
#define DREAM_ENGINE_HPP

//Logging
#include "Debug Tools/Logging.hpp"

//ECS core
#include "ECS/Component/ComponentList.hpp"
#include "ECS/System/SystemList.hpp"
#include "ECS/Entity/EntityManager.hpp"
#include "ECS/Coordinator.hpp"

//Math
#include "Math/MathLib.hpp"

//Management
#include "Management/ResourceManager.hpp"

//Game related
#include "Scene/GameScene.hpp"

//Layers
#include "Layer/Layer.hpp"
#include "Layer/LayerStack.hpp"


#endif