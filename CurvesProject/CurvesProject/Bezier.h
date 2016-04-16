#pragma once
#include "libs\glm\glm.hpp"
#include <vector>
#include <iostream>

using namespace glm;

class Bezier
{
private:
	std::vector<vec2> controlPoints;

public:
	Bezier();
	~Bezier();

	std::vector<vec2> GetControlPoints() const;
	std::vector<vec2> Curve(float step, float min, float max, vec2 p1, vec2 p2, vec2 p3, vec2 p4);
	vec2 Casteljau(std::vector<vec2> points, float step);
};

