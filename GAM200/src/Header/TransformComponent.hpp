#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "../Header/Math/Vector.hpp"

struct Transform {
	float x, y, z, 
		scaleX, scaleY, scaleZ;


	VectorND<float> position;
	VectorND<float> rotate;
	VectorND<int> scale;
};

#endif