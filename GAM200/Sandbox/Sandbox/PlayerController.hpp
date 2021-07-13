#pragma once
/*
NOTE: TESTING ONLY (WILL BE DELETED)
This file is only for testing purposes and will probably not be used
*/
#include "Debug Tools/Logging.hpp"
#include "Script/Script.hpp"

//-----------------------------------------------
#include "ECS/Coordinator.hpp"
extern Coordinator gCoordinator;
#define SPEED 200.f
//-----------------------------------------------

class PlayerController : public Script {
public:
	virtual void OnDestroy(const Entity& ent) override {  }
	virtual void Update(const Entity& ent, float dt) override {
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_W) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.y += SPEED * dt;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_S) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.y -= SPEED * dt;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_A) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.x -= SPEED * dt;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_D) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.x += SPEED * dt;
		}
	}

	//Your own functions
};

class AnotherController : public Script {
public:
	virtual void Init(const Entity& ent) override {  }
	virtual void Update(const Entity& ent, float dt) override {
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_I) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.y += SPEED * dt;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_K) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.y -= SPEED * dt;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_J) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.x -= SPEED * dt;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_L) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.x += SPEED * dt;
		}
	}

	//Your own functions
};

class CameraController : public Script {
public:
	virtual void Init(const Entity& ent) override {  }
	virtual void Update(const Entity& ent, float dt) override {
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_UP) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.y += SPEED * dt;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.y -= SPEED * dt;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.x -= SPEED * dt;
		}
		if (glfwGetKey(Window::GetGLFWwindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
			auto& transform1 = gCoordinator.GetCom<Transform>(ent);
			transform1.pos.x += SPEED * dt;
		}
	}

	//Your own functions
};