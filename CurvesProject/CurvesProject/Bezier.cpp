#include "Bezier.h"



Bezier::Bezier()
{
}


Bezier::~Bezier()
{
}

std::vector<vec2> Bezier::GetControlPoints() const
{
	return controlPoints;
}

std::vector<vec2> Bezier::Curve(float step) const
{
	std::vector<vec2> points = std::vector<vec2>();

	return points;
}

vec2 Bezier::Casteljau(std::vector<vec2> points, float step)
{
	if (points.size() == 1)
		return points[0];
	std::vector<vec2> newPoints;
	for (int i = 0; i < points.size() - 1; i++)
	{
		newPoints.push_back(points[i] * (1 - step) + points[i + 1] * step);
	}
	return Casteljau(newPoints, step);
}
