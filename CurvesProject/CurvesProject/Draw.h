#pragma once

#include <vector>
#include "Bezier.h"
#include "libs\glm\glm.hpp"

using std::vector;

class CurveObject {
	public:
		vector<glm::vec2> controlPoints;
		vector<glm::vec2> curvePoints;
		vector<vector<glm::vec2>> splineControlPoints;
		vector<vector<glm::vec2>> splineCurvePoints;
		vector<int> paramPoints;

		CurveObject() {
			controlPoints = vector<glm::vec2>();
			curvePoints = vector<glm::vec2>();
		}
};

void Render();

void initMenu();

void Initialize();

void mouse(int button, int state, int x, int y);

void mouseMotion(int x, int y);

void keyboard(unsigned char key, int xmouse, int ymouse);

void specialInput(int key, int x, int y);

void _CreateWindow();

// Fonction qui permet d'afficher du texte
void drawText(int x, int y, char *string, void *font);