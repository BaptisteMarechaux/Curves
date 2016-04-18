// CurvesProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>

#include "libs\glew\include\GL\glew.h"
#include "libs\freeglut\include\GL\freeglut.h"

#include <math.h>
#include "libs\glm\glm.hpp"

#include "Draw.h"
#include "Bezier.h"


int main(int argc, char* argv[])
{
	/*
	Bezier b = Bezier();

	b.Curve(0.25, vec2(0, 0), vec2(0, 1), vec2(1, 1), vec2(1, 0));

	int i(0);
	std::cin >> i;
	*/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	_CreateWindow();

	glutDisplayFunc(Render);
	// glutReshapeFunc(myReshape);
	initMenu();
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialInput);

	Initialize();

	glutMainLoop();

	return 0;

    return 0;
}

