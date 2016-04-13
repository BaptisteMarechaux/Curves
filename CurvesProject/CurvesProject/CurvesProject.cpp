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


int main(int argc, char* argv[])
{
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

	Initialize();

	glutMainLoop();

	return 0;

    return 0;
}

