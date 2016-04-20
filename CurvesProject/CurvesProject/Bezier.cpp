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

std::vector<vec2> Bezier::Spline(float step, float min, float max, vec2 p1, vec2 p2, vec2 p3, vec2 p4)
{
	std::vector<vec2> points = std::vector<vec2>();

	//points.push_back(p1);
	std::cout << "Starting Bezier" << std::endl;
	//std::cout << "X : " <<p1.x << " Y : " << p1.y << std::endl;

	for (float i = min; i <= max; i += step)
	{
		float t = i;

		float x = (pow(1 - t, 3)*p1.x + (pow(3*t, 3) - pow(6*t, 2) + 4)*p2.x + (pow(-3*t, 3) + pow(3*t, 2) + 3*t + 1)*p3.x + pow(t, 3)*p4.x) / 6;
		float y = (pow(1 - t, 3)*p1.y + (pow(3*t, 3) - pow(6*t, 2) + 4)*p2.y + (pow(-3*t, 3) + pow(3*t, 2) + 3*t + 1)*p3.y + pow(t, 3)*p4.y) / 6;
		std::cout << "X : " << x << " Y : " << y << std::endl;
		points.push_back(vec2(x, y));

	}


	//points.push_back(p4);
	//std::cout << "X : " << p4.x << " Y : " << p4.y << std::endl;

	return points;
}

std::vector<vec2> newPoints;
std::vector<vec2> returnPoints;

vec2 tmpCoord;

void getCasteljauPoint(int n, std::vector<vec2> points, float t) {

	std::vector<vec2> subTab = points;
	/*
	if (n == 1)
	{
		tmpCoord = points[0];
		newPoints.push_back(tmpCoord);
		std::cout << "X : " << tmpCoord.x << " Y : " << tmpCoord.y <<std::endl;
		return;
	}

	for (int i = 0; i < n - 1; i++)
	{
		float x = t * points[i].x + (1 - t)*points[i + 1].x;
		float y = t * points[i].y + (1 - t)*points[i + 1].y;
		subTab.push_back(vec2(x, y));
	}
	*/
	int s = 0;
	for (int j = 1; j < n; j++) {
		s = j;
		for (int i = 0; i < n - j; i++) {
			float x = (1 - t) * subTab[i].x + t*subTab[i + 1].x;
			float y = (1 - t) * subTab[i].y + t*subTab[i + 1].y;
			subTab[i] = (vec2(x, y));
			//newPoints.push_back(vec2(x, y));

		}
		//newPoints.push_back(subTab[0]);
		//newPoints.push_back(subTab[n-j-1]);
		//newPoints.insert(newPoints.end(), subTab.begin(), subTab.end());
	}
	newPoints.push_back(subTab[0]);
	//newPoints = subTab;

	//getCasteljauPoint(n - 1, subTab, t);
}

std::vector<vec2> Bezier::CasteljauBezier(std::vector<vec2> points, float step, float min, float max)
{
	//vec2 tmp;
	//newPoints = points;
	//returnPoints = std::vector<vec2>();
	
	for (float t = min; t <= max; t += step) {
		getCasteljauPoint(points.size(), points, t);
		//returnPoints.push_back(tmp);
	}
	return newPoints;
}

std::vector<vec2> Bezier::Raccord(int level, std::vector<vec2> points, float r0, float r1, float step)
{
	std::vector<vec2> returnPoints = std::vector<vec2>();
	std::vector<vec2> tmp;
	switch (level)
	{
	case 0:
		returnPoints =  (CasteljauBezier(points, step, 0, 1));
		
		break;

	case 1:
		returnPoints = points;
		returnPoints.push_back(points[points.size() - 2] + points[points.size() - 1]);
		break;

	case 2:
		//n(t)=(1-t)P1+P2
		returnPoints = points;
		returnPoints.push_back(points[points.size() - 3] + points[points.size() - 2]);
		returnPoints.push_back( points[points.size()-2] + points[points.size()-1]);
		break;
	default:
		break;
	}
	return returnPoints;
}
