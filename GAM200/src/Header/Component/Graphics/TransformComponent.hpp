#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "Math/Vector.hpp"

struct Transform {
	MathD::Vec3 position = MathD::Vec3{}; // x and y for 2d position and z for the layering (whether it appear on top or below)
	MathD::Vec2 scale = MathD::Vec2{};
	float rotation = float{}; // in degree

	Transform() = default;
	Transform(MathD::Vec3 pos, MathD::Vec2 s, float r) :
		position{ pos }, scale{ s }, rotation{ r } {}

private:
	//matrix for model to ndc transform
	//MathD::Mat3 mdl_to_ndc = MathD::Mat3{};
};

#endif