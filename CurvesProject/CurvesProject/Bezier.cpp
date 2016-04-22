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

/*
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
*/

std::vector<vec2> newPoints;
std::vector<vec2> returnPoints;

vec2 tmpCoord;

void getCasteljauPoint(int n, std::vector<vec2> points, float t, float min, float max) {

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
			float x = ((max - t) / (max - min)) * subTab[i].x + ((t-min) / (max-min))*subTab[i + 1].x;
			float y = ((max - t) / (max - min)) * subTab[i].y + ((t - min) / (max - min))*subTab[i + 1].y;
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

std::vector<vec2> Bezier::CasteljauBezier(std::vector<vec2> points, float step, std::vector<int> paramSpace)
{
	//vec2 tmp;
	//newPoints = points;
	//returnPoints = std::vector<vec2>();
	float intistep = step;
	newPoints.clear();
	/*for (int i = 0; i < paramSpace.size()-1; i ++) {
		step = (paramSpace[i + 1] - paramSpace[i]) / intistep;
		for (float t = paramSpace[i]; t <= paramSpace[i + 1]; t += step) {
			getCasteljauPoint(points.size(), points, t, paramSpace[i], paramSpace[i + 1]);
			//returnPoints.push_back(tmp);
		}
	}*/
		step = (paramSpace[1] - paramSpace[0]) / intistep;
		for (float t = paramSpace[0]; t <= paramSpace[1]; t += step) {
			getCasteljauPoint(points.size(), points, t, paramSpace[0], paramSpace[1]);
			//returnPoints.push_back(tmp);
		}
	newPoints.push_back(points[points.size()-1]);
	return newPoints;
}

std::vector<vec2> Bezier::Raccord(int level, std::vector<vec2> points, std::vector<int> paramSpace)
{
	std::vector<vec2> returnPoints = std::vector<vec2>();
	std::vector<vec2> tmp;
	vec2 vect;
	vec2 vect2;
	vec2 vect3;
	switch (level)
	{
	case 0:
		//returnPoints =  (CasteljauBezier(points, step, 0, 1));
		returnPoints.push_back(points[points.size() - 1]);
		break;

	case 1:
		returnPoints.push_back(points[points.size() - 1]);
		// Vecteur
		vect = points[points.size() - 1] - points[points.size() - 2];
		// Normalisation
		vect *= (1.0 / vect.length());
		// Facteur
		//vect *= ((paramSpace[1]- paramSpace[0]) + (paramSpace[2] - paramSpace[1]))/ (paramSpace[1] - paramSpace[0]);
		vect *= (paramSpace[0] + paramSpace[1]) / (paramSpace[0]);
		returnPoints.push_back(points[points.size() - 1] + vect);
		break;
	case 2:
		//n(t)=(1-t)P1+P2
		returnPoints.push_back(points[points.size() - 1]);
		vect = points[points.size() - 1] - points[points.size() - 2];
		//vect *= (1.0 / vect.length());
		vect *= (paramSpace[0] + paramSpace[1]) / paramSpace[0];
		vect = points[points.size() - 1] + vect;
		returnPoints.push_back(vect);
		vect2 = points[points.size() - 2] - points[points.size() - 3];
		vect2 *= (1.0 / vect2.length());
		vect2 *= 2;
		// Point intermediaire
		vect2 = points[points.size() - 2] + vect2;
		vect3 = vect - vect2;
		//vect3 *= (1.0 / vect3.length());
		vect3 *= (paramSpace[0] + paramSpace[1]) / paramSpace[0];
		returnPoints.push_back(vect + vect3);
		break;
	default:
		break;
	}
	return returnPoints;
}


void Bezier::Spline(std::vector<vec2> points, std::vector<float> nodalVec, bool version1)
{
	
	std::vector<vec2> frags = std::vector<vec2>();
	currentCurveObjects = std::vector<std::vector<vec2>>();
	/*
	if (points.size() < 4)
	{
		newCurves[0].controlPoints = points;
		return std::vector<vec2>();
	}
	*/



	frags.push_back(points[0]);
	frags.push_back(points[1]);
	//On va parcourir les points de la courbes sans avoir à couper le premier et le dernier segment
	int nodalindex = 0;
	for (int i = 1; i < points.size() - 2; i++)
	{
		//prend le 2tier et rajoute le premier tiers du suivant :)
		vec2 f((points[i + 1] - points[i]) * 0.667f + points[i]);

		//On met un premier point du segment en cours
		frags.push_back(f);

		vec2 s((points[i + 2] - points[i + 1]) * 0.333f + points[i + 1]);

		//---
		frags.push_back((s - f)*0.333f + f);

		frags.push_back(s);

	}
	frags.push_back(points[points.size()-2]);
	frags.push_back(points[points.size()-1]);

	if(version1)
	for (int i = 0; i < frags.size(); i += 3) {
		std::vector<vec2> temp = std::vector<vec2>();
		if (frags.size() - i - 1 > 3) {
			
			temp.push_back(frags[i]);
			temp.push_back(frags[i+1]);
			temp.push_back(frags[i+2]);
			temp.push_back(frags[i+3]);
			currentCurveObjects.push_back(temp);
		}
		else
		{
			for (int j = i; j < frags.size(); j++) {
				temp.push_back(frags[j]);
			}
			currentCurveObjects.push_back(temp);
		}
	}
	else
	{
		currentCurveObjects.push_back(frags);
	}

	std::cout << "Frags : " << frags.size() << std::endl;

	return;
}

vec2 Bezier::deBoor(int k, int degree, int i, float x, std::vector<float> knots, std::vector<vec2> ctrlPoints)
{

	return vec2();
}