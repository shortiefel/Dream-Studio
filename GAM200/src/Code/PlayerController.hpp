#pragma once
/*
This file is only for testing purposes and will probably not be used
*/
#include "Debug Tools/Logging.hpp"
#include "Script/Script.hpp"

//-----------------------------------------------
#include "Coordinator/Coordinator.hpp"
extern Coordinator gCoordinator;
//-----------------------------------------------

class PlayerController : public Script {
public:
	virtual void OnDestroy(const Entity& ent) override { LOG_INFO("player destroy"); }
	virtual void Update(const Entity& ent, float dt) override {
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.y += 2.f;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.y -= 2.f;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.x -= 2.f;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.x += 2.f;
		}
	}

	//Your own functions
};

class AnotherController : public Script {
public:
	virtual void Init(const Entity& ent) override { LOG_INFO("Another Init"); }
	virtual void Update(const Entity& ent, float dt) override {
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_I) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.y += 2.f;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_K) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.y -= 2.f;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_J) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.x -= 2.f;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_L) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.x += 2.f;
		}
	}

	//Your own functions
};