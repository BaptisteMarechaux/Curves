#include "Bezier2D.h"

using namespace glm;

int Factorial(int n)
{
	int res = n;
	for (int i = n-1; i > 0; i--)
	{
		res *= i;
	}
	return res;
}

float Combination(float subEnsemble, float ensemble) //subEmsemble : i , Ensemble : n
{
	if (subEnsemble > ensemble) {
		std::cout << "Le sous ensemble est plus grand que l'ensemble" << std::endl;
		std::swap(subEnsemble, ensemble);
	}
	return Factorial(ensemble)/((float)(Factorial(subEnsemble)*Factorial(ensemble-subEnsemble)));
}

float Bernstein(float subEnsemble, float ensemble, float t) //subEmsemble : i , Ensemble : n
{
	return Combination(subEnsemble, ensemble) * pow(t, subEnsemble) *  pow((1 - t), ensemble - subEnsemble);
}

void BezierCurve4(std::vector<vec2> points)
{
	
}
