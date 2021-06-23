#ifndef GUILAYER_H
#define GUILAYER_H

#include "Layer.hpp"

struct GLFWwindow;

class GUILayer : public Layer{
public:
	static bool Create(GLFWwindow* window, const char* glsl_version); 
	static void Destroy();
	inline static GUILayer* Get() { return m_instance; }

	virtual void Draw() override;
	virtual void Update() override;
	virtual bool OnEvent(Event& e) override;
private:
	static GUILayer* m_instance;
};

#endif