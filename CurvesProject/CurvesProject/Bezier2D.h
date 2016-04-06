#pragma once
#include <vector>
#include <iostream>

#include "libs\glm\glm.hpp"
#include "libs\glm\gtc\constants.hpp"

using namespace glm;

int Factorial(int n);

float Combination(float subEnsemble, float ensemble);

float Bernstein(float subEnsemble, float ensemble);

void BezierCurve4(std::vector<vec2> points);

