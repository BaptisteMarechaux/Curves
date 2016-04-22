#pragma once
#include "libs\glm\glm.hpp"
#include <vector>
#include <iostream>
#include "Draw.h"

using namespace glm;

class Bezier
{
private:
	std::vector<vec2> controlPoints;

public:
	Bezier();
	~Bezier();

	std::vector<std::vector<vec2>> currentCurveObjects;

	std::vector<vec2> GetControlPoints() const;
	std::vector<vec2> Curve(float step, float min, float max, vec2 p1, vec2 p2, vec2 p3, vec2 p4);
	vec2 Casteljau(std::vector<vec2> points, float step);
	//std::vector<vec2> Spline(float step, float min, float max, vec2 p1, vec2 p2, vec2 p3, vec2 p4);
	//std::vector<vec2> CasteljauBezier(std::vector<vec2> points, float step, float min, float max);
	std::vector<vec2> CasteljauBezier(std::vector<vec2> points, float step, std::vector<int> paramSpace);

	//Raccordements avec des niveau allant de 0 à 2 C0, C1, C2
	//std::vector<vec2> Raccord(int level, std::vector<vec2> points, float r0, float r1, float step);
	std::vector<vec2> Bezier::Raccord(int level, std::vector<vec2> points, std::vector<int> paramSpace);

	void Spline(std::vector<vec2> points, std::vector<float> nodalVec, bool version1);

	vec2 deBoor(int k, int degree, int i, float x, std::vector<float> knots, std::vector<vec2> ctrlPoints);
};

