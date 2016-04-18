#pragma once

typedef GLfloat color[3];

struct _Point
{
	GLint x, y;
};

#include <vector>
#include "Bezier.h"
#include "libs\glm\glm.hpp"
using std::vector;

class PointArray
{
public:
	vector<_Point> points;
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