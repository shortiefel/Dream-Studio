#ifndef LAYER_H
#define LAYER_H

class Event;

class Layer {
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool OnEvent(Event& e) = 0;
//private:
//	bool isActive = true;
// instead can check if graphic component is active or not
};

#endif