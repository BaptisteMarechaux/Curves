#pragma once
#include "libs\glm\glm.hpp"
#include <vector>

using namespace glm;

class Bezier
{
private:
	std::vector<vec2> controlPoints;

public:
	Bezier();
	~Bezier();

	std::vector<vec2> GetControlPoints() const;
	std::vector<vec2> Curve(float step) const;
	vec2 Casteljau(std::vector<vec2> points, float step);
};

