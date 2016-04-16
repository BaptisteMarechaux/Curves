#pragma once

// C, standard, dio
#include <cstdio>
// C, standard, int
#include <cstdint>
#include "GL/freeglut.h"
#include <iostream>
#include "libs\glm\glm.hpp"

// Pour les fonctions
#include "Draw.h"

using namespace std;

// Pour les tableaux
#include <vector>

// Enregistre les coordonnées de la souris
GLint mousex;
GLint mousey;

// Enregistre la taille de la fenêtre
GLint Win;

// Index du mode pour le traçage des formes
int indexPolyMode=3;
// Index du mode général
int mode; // 1 = Poly
bool modifying = false;
int indexOfModifyingPoly = 0;
int indexOfModifyingPoint = 0;
int modifyingMode = 0;

bool leftButtonPressed = false;

// Tableaux de points pour les formes à l'écran
vector<PointArray> polys;
int currentPoly = 0;

vector<PointArray> controlPoints;

//Couleur selectionnée pour les formes
vector<int>polyColor = { 2 };

float x1, x2, x3, x4, y5, y2, y3, y4;
bool pointSelected = false;
bool showCredits;

_Point currentParameterSpace = { 0, 1 };

// Pas
int nStep = 1;

// Dimmension du repère de la fenêtre
int hmax = 800, vmax = 600, hmin=0, vmin=0;

// Définition de la couleur de remplissager
color redColor = { 1.0f, 0.0f, 0.0f };
color blueColor = { 0.0f, 0.0f, 1.0f };
color greenColor = { 0.0f, 1.0f, 0.0f };
color blackColor = { 0.0f, 0.0f, 0.0f };
color purpleColor = { 0.75f, 0.0f, 0.75f };

Bezier bezier = Bezier();

//B Curve ArrayPoint
vector<glm::vec2> bPoints;
vector<glm::vec2> casPoints = vector<glm::vec2>();

void Initialize() 
{
	glClearColor(1.0, 0.984, 0.906, 0.961);
	glColor3f(0.0f, 0.0f, 1.0f);
	glPointSize(2.0);			
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();	

	gluOrtho2D(0.0, (GLdouble)800,
		(GLdouble)600, 0.0);

	PointArray firstPoly;
	polys.push_back(firstPoly);

	PointArray firstPoly2;
	controlPoints.push_back(firstPoly2);
}

// Rendu des formes dans la fenêtre
void Render()
{
	// Nettoyage de la fenêtre
	glClear(GL_COLOR_BUFFER_BIT);

	// On trace le poly en fonction du mode de traçage choisi
	switch (indexPolyMode) {
	case 1:
		for (int p = 0; p < polys.size(); p++)
		{
			// On choisi la couleur du poly
			switch (polyColor[p]) {
			case 1:
				glColor3fv(redColor);
				break;
			case 2:
				glColor3fv(blueColor);
				break;
			case 3:
				glColor3fv(greenColor);
				break;
			case 4:
				glColor3fv(blackColor);
				break;
			case 5:
				glColor3fv(purpleColor);
				break;
			}
			glBegin(GL_POINTS);
			for (int i = 0; i < polys[p].points.size(); i++) {
				glVertex2i(polys[p].points[i].x, polys[p].points[i].y);
			}
			/*
			for (int i = 0; i < bPoints.size(); i++) {
				glVertex2i(bPoints[i].x, bPoints[i].y);
			}
			*/
			glEnd();
		}
		break;
	case 2:
		for (int p = 0; p < polys.size(); p++)
		{
			// On choisi la couleur du poly
			switch (polyColor[p]) {
			case 1:
				glColor3fv(redColor);
				break;
			case 2:
				glColor3fv(blueColor);
				break;
			case 3:
				glColor3fv(greenColor);
				break;
			case 4:
				glColor3fv(blackColor);
				break;
			case 5:
				glColor3fv(purpleColor);
				break;
			}
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < polys[p].points.size(); i++) {
				glVertex2i(polys[p].points[i].x, polys[p].points[i].y);
			}
			for (int i = 0; i < bPoints.size(); i++) {
				glVertex2i(bPoints[i].x, bPoints[i].y);
			}
			glEnd();
		}
		glEnd();
		break;
	case 3:
		for (int p = 0; p < polys.size(); p++)
		{
			// On choisi la couleur du poly
			switch (polyColor[p]) {
			case 1:
				glColor3fv(redColor);
				break;
			case 2:
				glColor3fv(blueColor);
				break;
			case 3:
				glColor3fv(greenColor);
				break;
			case 4:
				glColor3fv(blackColor);
				break;
			case 5:
				glColor3fv(purpleColor);
				break;
			}
			/*
			glBegin(GL_LINE_LOOP);
			for (int i = 0; i < polys[p].points.size(); i++) {
				glVertex2i(polys[p].points[i].x, polys[p].points[i].y);
			}
			glEnd();
			*/
			glBegin(GL_LINE_LOOP);
			casPoints = vector<glm::vec2>(controlPoints[p].points.size(), vec2(0, 0));
			for (int i = 0; i < controlPoints[p].points.size(); i++) {
				glVertex2i(controlPoints[p].points[i].x, controlPoints[p].points[i].y);
				
			}

			/*
			if (controlPoints[p].points.size() >= 4) {
				for (int i = 0; i < casPoints.size(); i++) {
					glVertex2i(casPoints[i].x, casPoints[i].y);
				}
			}
			*/
			
			for (int i = 0; i < bPoints.size(); i++) {
				glVertex2i(bPoints[i].x, bPoints[i].y);
			}
			

			glEnd();
		}
		break;

	default:
		break;
	}
	

	//Affiche les crédits
	if (showCredits) {
		glColor3f(0.25, 0.25, 0.25);
		// Donne la position du texte, le texte et les caractéristiques de sa police
		drawText(10, 30, "Baptiste Marechaux & Julien Geiger", GLUT_BITMAP_9_BY_15);
	}

	glFlush();
}

// Fonction d'evenements à la souris
void mouse(int button, int state, int x, int y)
{
	//Si on effectue un clic gauche
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		mousex = x;
		mousey = y;
		std::cout << x << " " << y << "\n";
		_Point tmpPoint;
		tmpPoint.x = mousex;
		tmpPoint.y = mousey;
		_Point tmpPoint2;
		tmpPoint2.x = mousex + 10;
		tmpPoint2.y = mousey - 20;
		if (mode == 1) {
			polys[currentPoly].points.push_back(tmpPoint);
			controlPoints[currentPoly].points.push_back(tmpPoint2);
			if (controlPoints[currentPoly].points.size() == 4) {
				Bezier b = Bezier();
				
				glm::vec2 v = glm::vec2(0, 0);
				bPoints = b.Curve(0.05,0, 1, glm::vec2(controlPoints[currentPoly].points[0].x,controlPoints[currentPoly].points[0].y),
					glm::vec2(controlPoints[currentPoly].points[1].x, controlPoints[currentPoly].points[1].y),
					glm::vec2(controlPoints[currentPoly].points[2].x, controlPoints[currentPoly].points[2].y),
					glm::vec2(controlPoints[currentPoly].points[3].x, controlPoints[currentPoly].points[3].y)
				);
			}

		}


		leftButtonPressed = false;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		indexOfModifyingPoly = 0;
		indexOfModifyingPoint = 0;
		modifyingMode = 0;

		for (int p = 0; p < controlPoints.size(); p++)
		{
			for (unsigned int i = 0; i < controlPoints[p].points.size(); i++) {
				if (sqrt((x - controlPoints[p].points[i].x)*(x - controlPoints[p].points[i].x) + (y - controlPoints[p].points[i].y)*(y - controlPoints[p].points[i].y)) < 15) {
					indexOfModifyingPoly = p;
					indexOfModifyingPoint = i;
					modifyingMode = 1;
					leftButtonPressed = true;
					break;
				}
			}
			if (indexOfModifyingPoly != 0)
				break;
		}
	}

	glutPostRedisplay();
}

void mouseMotion(int x, int y) {
	if (modifying && leftButtonPressed) {
		if (modifyingMode == 1) {
			controlPoints[indexOfModifyingPoly].points[indexOfModifyingPoint].x = x;
			controlPoints[indexOfModifyingPoly].points[indexOfModifyingPoint].y = y;
		}
	}
	glutPostRedisplay();
}

// Procédés appelés au clavier
void keyboard(unsigned char key, int xmouse, int ymouse)
{
	// En fonction de la touche
	switch (key) {
	// On change la couleur de fond
	case 97:
		glClearColor(1.0, 0.984, 0.906, 0.961);
		std::cout << "clear";
		break;
	// On change la couleur de fond
	case 122:
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		std::cout << "clear";
		break;
	// On quitte l'application avec la touche echap
	case 27:
		glutDestroyWindow(Win);
		exit(0);
		break;
	// On zoom avec le + du pavé numérique
	case '+':
		nStep += 1;
		break;

	// On dé-zoom avec le - du pavé numérique
	case '-':
		nStep -= 1;
		break;

	default:
		break;
	}
	// Demande de le redessin de la fenêtre
	glutPostRedisplay();
}

// Fonction de menu principal
void processMenuEvents(int option) {
	switch (option) {
		// Bouton qui permet de quitter l'application
	case 0:
		glutDestroyWindow(Win);
		exit(0);
		break;
	}
	modifying = false;

	// Demande de le redessin de la fenêtre
	glutPostRedisplay();
}

void prop_menu(int option) {
	switch (option) {
	case 1:
		break;
	case 2:
			break;
	}
	modifying = false;
	glutPostRedisplay();
}

// Fonction du menu qui permet de changer la couleur de la forme dessinée
void colors_menu(int option) {
		if (polyColor.size() != 0) {
			polyColor[currentPoly] = option;
		}
		else
		{
			polyColor.push_back(option);
		}
	// Demande de le redessin de la fenêtre
	glutPostRedisplay();
}

// Fonction du menu qui permet de changer la nature de la forme dessinée
void polyCut_menu(int option) {
	mode = 1;

	if (polys.size() != 0) {
		if (polys[currentPoly].points.size() > 3) {
			PointArray tmpPoly;
			polys.push_back(tmpPoly);
			PointArray tmpPoly2;
			controlPoints.push_back(tmpPoly2);
			polyColor.push_back(2);
			currentPoly++;
		}
		else
		{
			polys[currentPoly].points.clear();
			controlPoints[currentPoly].points.clear();
		}
	}

	modifying = false;

	glutPostRedisplay();
}

// Menu doption supplémentaires
void option_menu(int option) {
	switch (option) {
	// Nettoie la fenêtre et les structures
	case 1:
		modifying = !modifying;
		mode = 0;
		break;
	case 3:
		polys.clear();
		currentPoly = 0;
		Initialize();
		indexPolyMode = 3;
		mode = 0;
		break;
	// Affiche les crédits
	case 4:
		showCredits = !showCredits;
		break;
	}
	glutPostRedisplay();
}

// Initialise le menu
void initMenu() {

	// Index du menu
	int menu;
	// Création du menu
	menu = glutCreateMenu(processMenuEvents);

	// Liste des index des sous menus
	GLint colorsMenu, polyCutMenu, propMenu, optionMenu;

	// Menu pour changer la couleur
	colorsMenu = glutCreateMenu(colors_menu);
	// Liste des couleurs disponibles
	glutAddMenuEntry("Rouge", 1);
	glutAddMenuEntry("Bleu", 2);
	glutAddMenuEntry("Vert", 3);
	glutAddMenuEntry("Noir", 4);
	glutAddMenuEntry("Violet", 5);

	polyCutMenu = glutCreateMenu(polyCut_menu);
	glutAddMenuEntry("Courbe de Bezier", 1);

	propMenu = glutCreateMenu(prop_menu);
	glutAddMenuEntry("Espace de paramétrage", 1);
	glutAddMenuEntry("Pas", 2);

	optionMenu = glutCreateMenu(option_menu);
	glutAddMenuEntry("Modifier", 1);
	glutAddMenuEntry("Remise à zero", 3);
	glutAddMenuEntry("Credits", 4);

	glutCreateMenu(processMenuEvents);
	glutAddSubMenu("Colours", colorsMenu);
	glutAddSubMenu("Créer une courbe", polyCutMenu);
	glutAddSubMenu("Propriétés", propMenu);
	glutAddSubMenu("Options", optionMenu);
	glutAddMenuEntry("Quitter", 0);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void _CreateWindow() {
	Win = glutCreateWindow("Window");
}

// Fonction qui permet d'afficher du texte
void drawText(int x, int y, char *string, void *font)
{
	// Positionne le premier caractère de la chaîne
	glRasterPos2f(x, y);
	// Calcule la longueur de la chaîne de caractères
	int len = (int)strlen(string);
	// Affiche tout les caractères en fonctin de la police
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}
