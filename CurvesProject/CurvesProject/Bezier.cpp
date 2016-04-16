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

std::vector<vec2> Bezier::Curve(float step, float min, float max, vec2 p1, vec2 p2, vec2 p3, vec2 p4)
{
	std::vector<vec2> points = std::vector<vec2>();

	//points.push_back(p1);
	std::cout << "Starting Bezier" << std::endl;
	//std::cout << "X : " <<p1.x << " Y : " << p1.y << std::endl;

	for (float i = min; i <= max; i += step)
	{
		float t = i;
		float x = pow(1 - t, 3)*p1.x + 3 * t*pow(1 - t, 2)*p2.x + 3 * pow(t, 2)*(1 - t)*p3.x + pow(t, 3)*p4.x;
		float y = pow(1 - t, 3)*p1.y + 3 * t*pow(1 - t, 2)*p2.y + 3 * pow(t, 2)*(1 - t)*p3.y + pow(t, 3)*p4.y;

		std::cout << "X : " << x << " Y : " << y << std::endl;
		points.push_back(vec2(x, y));

	}

	//points.push_back(p4);
	//std::cout << "X : " << p4.x << " Y : " << p4.y << std::endl;

	return points;
}

vec2 Bezier::Casteljau(std::vector<vec2> points, float step)
{
	if (points.size() == 1) {
		std::cout << "X : " << points[0].x << " Y : " << points[0].y << std::endl;
		return points[0];
	}
		
	std::vector<vec2> newPoints;
	for (int i = 0; i < points.size() - 1; i++)
	{
		newPoints.push_back(points[i] *step + points[i + 1] * (1-step) );
	}
	Casteljau(newPoints, step);
}
