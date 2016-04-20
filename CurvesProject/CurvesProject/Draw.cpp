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

//B Curve ArrayPoint
vector<CurveObject> curves;

int currentCurve = 0;

//Couleur selectionnée pour les formes
vector<int>polyColor = { 2 };

float x1, x2, x3, x4, y5, y2, y3, y4;
bool pointSelected = false;
bool showCredits;

glm::vec2 currentParameterSpace = { 0, 1 };

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

vector<glm::vec2> casPoints = vector<glm::vec2>();


float tMatrix[16] = { 1,0,0,10, 0,1,0,10, 0,0,1,10, 0,0,0,10 };
float ntMatrix[16] = { 1,0,0,-10, 0,1,0,-10, 0,0,1,-10, 0,0,0,-10 };
float rMatrix[16] = { cos(10),-sin(10),0,0, sin(10),cos(10),0,0, 0,0,1,0, 0,0,0,1 };
float nrMatrix[16] = { cos(10),-sin(10),0,0, sin(10),cos(10),0,0, 0,0,1,0, 0,0,0,1 };
float sMatrix[16] = { 1.1,0,0,0, 0,1.1,0,0, 0,0,1.1,0, 0,0,0,0 };
float nsMatrix[16] = { 0.9,0,0,0, 0,0.9,0,0, 0,0,0.9,0, 0,0,0,0 };
float cMatrix[16] = { 1,0,0,0, 0.5f,1,0,0, 0,0,1,0, 0,0,0,0 };

int modifierType = 0;

void Initialize() 
{
	glClearColor(1.0, 0.984, 0.906, 0.961);
	glColor3f(0.0f, 0.0f, 1.0f);
	// Taille des points
	glPointSize(7.0);			
	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();	

	gluOrtho2D(0.0, (GLdouble)800,
		(GLdouble)600, 0.0);

	//polyColor.push_back(2);

	CurveObject firstPoly;
	curves.push_back(firstPoly);
}

// Rendu des formes dans la fenêtre
void Render()
{
	// Nettoyage de la fenêtre
	glClear(GL_COLOR_BUFFER_BIT);

	if (curves[currentCurve].controlPoints.size() >= 4) {
		Bezier b = Bezier();

		glm::vec2 v = glm::vec2(0, 0);
		curves[currentCurve].curvePoints = b.Curve(0.05, 0, 1, glm::vec2(curves[currentCurve].controlPoints[0].x, curves[currentCurve].controlPoints[0].y),
			glm::vec2(curves[currentCurve].controlPoints[1].x, curves[currentCurve].controlPoints[1].y),
			glm::vec2(curves[currentCurve].controlPoints[2].x, curves[currentCurve].controlPoints[2].y),
			glm::vec2(curves[currentCurve].controlPoints[3].x, curves[currentCurve].controlPoints[3].y)
			);
	}

	// On trace le poly en fonction du mode de traçage choisi
	switch (indexPolyMode) {
	case 3:
		for (int p = 0; p < curves.size(); p++)
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
			//casPoints = vector<glm::vec2>(curves[p].curvePoints.size(), vec2(0, 0));
			glBegin(GL_POINTS);
			for (int i = 0; i < curves[p].controlPoints.size(); i++) {
				glVertex2i(curves[p].controlPoints[i].x, curves[p].controlPoints[i].y);
			}
			glEnd();
			/*
			if (curves[p].points.size() >= 4) {
				for (int i = 0; i < casPoints.size(); i++) {
					glVertex2i(casPoints[i].x, casPoints[i].y);
				}
			}
			*/
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < curves[p].curvePoints.size(); i++) {
				glVertex2i(curves[p].curvePoints[i].x, curves[p].curvePoints[i].y);
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
		vec2 tmpPoint;
		tmpPoint.x = mousex;
		tmpPoint.y = mousey;
		if (mode == 1) {
			curves[currentCurve].controlPoints.push_back(tmpPoint);
		}


		leftButtonPressed = false;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		indexOfModifyingPoly = 0;
		indexOfModifyingPoint = 0;
		modifyingMode = 0;

		for (int p = 0; p < curves.size(); p++)
		{
			for (unsigned int i = 0; i < curves[p].controlPoints.size(); i++) {
				if (sqrt((x - curves[p].controlPoints[i].x)*(x - curves[p].controlPoints[i].x) + (y - curves[p].controlPoints[i].y)*(y - curves[p].controlPoints[i].y)) < 15) {
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
			curves[indexOfModifyingPoly].controlPoints[indexOfModifyingPoint].x = x;
			curves[indexOfModifyingPoly].controlPoints[indexOfModifyingPoint].y = y;
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

// Procédés appelés au clavier
void specialInput(int key, int x, int y)
{
	int _x = 0;
	int _y = 0;

	// En fonction de la touche
	switch (key) {
	case GLUT_KEY_UP:    // key up
		switch (modifierType)
		{
		case 1:
			for (size_t i = 0; i < curves[currentCurve].controlPoints.size(); i++)
			{
				_y = curves[currentCurve].controlPoints[i].y;
				curves[currentCurve].controlPoints[i].y = ntMatrix[4] * _y + ntMatrix[5] * _y + ntMatrix[6] * _y + ntMatrix[7];
			}
			break;
		}
		break;
	case GLUT_KEY_DOWN:    // key down
		switch (modifierType)
		{
		case 1:
			for (size_t i = 0; i < curves[currentCurve].controlPoints.size(); i++)
			{
				_y = curves[currentCurve].controlPoints[i].y;
				curves[currentCurve].controlPoints[i].y = tMatrix[4] * _y + tMatrix[5] * _y + tMatrix[6] * _y + tMatrix[7];
			}
			break;
		}
	case GLUT_KEY_RIGHT:    // key right
		switch (modifierType)
		{
		case 1:
			for (size_t i = 0; i < curves[currentCurve].controlPoints.size(); i++)
			{
				_x = curves[currentCurve].controlPoints[i].x;
				curves[currentCurve].controlPoints[i].x = tMatrix[0] * _x + tMatrix[1] * _x + tMatrix[2] * _x + tMatrix[3];

			}
			break;
		case 3:
			for (size_t i = 0; i < curves[currentCurve].controlPoints.size(); i++)
			{
				_x = curves[currentCurve].controlPoints[i].x;
				curves[currentCurve].controlPoints[i].x = sMatrix[0] * _x + sMatrix[1] * _x + sMatrix[2] * _x + sMatrix[3];
				_y = curves[currentCurve].controlPoints[i].y;
				curves[currentCurve].controlPoints[i].y = sMatrix[4] * _y + sMatrix[5] * _y + sMatrix[6] * _y + sMatrix[7];
			}
			break;
		}
		break;
	case GLUT_KEY_LEFT:    // key left
		switch (modifierType)
		{
		case 1:
			for (size_t i = 0; i < curves[currentCurve].controlPoints.size(); i++)
			{
				_x = curves[currentCurve].controlPoints[i].x;
				curves[currentCurve].controlPoints[i].x = ntMatrix[0] * _x + ntMatrix[1] * _x + ntMatrix[2] * _x + ntMatrix[3];

			}
			break;
		case 2:
			for (size_t i = 0; i < curves[currentCurve].controlPoints.size(); i++)
			{
				/*_x = curves[currentCurve].controlPoints[i].x;
				curves[currentCurve].controlPoints[i].x = nrMatrix[0] * _x + nrMatrix[1] * _x + nrMatrix[2] * _x + nrMatrix[3];
				_y = curves[currentCurve].controlPoints[i].y;
				curves[currentCurve].controlPoints[i].y = nrMatrix[4] * _y + nrMatrix[5] * _y + nrMatrix[6] * _y + nrMatrix[7];*/
			}
			break;
		case 3:
			for (size_t i = 0; i < curves[currentCurve].controlPoints.size(); i++)
			{
				_x = curves[currentCurve].controlPoints[i].x;
				curves[currentCurve].controlPoints[i].x = nsMatrix[0] * _x + nsMatrix[1] * _x + nsMatrix[2] * _x + nsMatrix[3];
				_y = curves[currentCurve].controlPoints[i].y;
				curves[currentCurve].controlPoints[i].y = nsMatrix[4] * _y + nsMatrix[5] * _y + nsMatrix[6] * _y + nsMatrix[7];
			}
			break;
		}
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

void mod_menu(int option) {
	switch (option) {
	case 0:
		modifierType = 1;
		break;
	case 1:
		modifierType = 2;
		break;
	case 2:
		modifierType = 3;
		break;
	case 3:
		modifierType = 4;
		break;
	}
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
			polyColor[currentCurve] = option;
		}
		else
		{
			polyColor.push_back(option);
		}
	// Demande de le redessin de la fenêtre
	glutPostRedisplay();
}

// Fonction du menu qui permet de changer la nature de la forme dessinée
void polyMade_menu(int option) {
	mode = 1;

	switch (option) {
		// Nettoie la fenêtre et les structures
	case 1:
		if (curves.size() != 0) {
			if (curves[currentCurve].controlPoints.size() > 3) {
				CurveObject tmpPoly;
				curves.push_back(tmpPoly);
				polyColor.push_back(2);
				currentCurve++;
			}
			else
			{
				curves[currentCurve].controlPoints.clear();
				curves[currentCurve].controlPoints.clear();
			}
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
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
		curves.clear();
		currentCurve = 0;
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
	GLint colorsMenu, polyMadeMenu, modMenu, propMenu, optionMenu;

	// Menu pour changer la couleur
	colorsMenu = glutCreateMenu(colors_menu);
	// Liste des couleurs disponibles
	glutAddMenuEntry("Rouge", 1);
	glutAddMenuEntry("Bleu", 2);
	glutAddMenuEntry("Vert", 3);
	glutAddMenuEntry("Noir", 4);
	glutAddMenuEntry("Violet", 5);

	polyMadeMenu = glutCreateMenu(polyMade_menu);
	glutAddMenuEntry("Courbe de Bezier", 1);
	glutAddMenuEntry("Raccordement C0", 2);
	glutAddMenuEntry("Raccordement C1", 3);
	glutAddMenuEntry("Raccordement C2", 4);

	propMenu = glutCreateMenu(prop_menu);
	glutAddMenuEntry("Espace de paramétrage", 1);
	glutAddMenuEntry("Pas", 2);

	modMenu = glutCreateMenu(mod_menu);
	glutAddMenuEntry("Translation", 0);
	glutAddMenuEntry("Rotation", 1);
	glutAddMenuEntry("Scale", 2);
	glutAddMenuEntry("cisaillement", 3);

	optionMenu = glutCreateMenu(option_menu);
	glutAddMenuEntry("Modifier", 1);
	glutAddMenuEntry("Remise à zero", 3);
	glutAddMenuEntry("Credits", 4);

	glutCreateMenu(processMenuEvents);
	glutAddSubMenu("Colours", colorsMenu);
	glutAddSubMenu("Créer une courbe", polyMadeMenu);
	glutAddSubMenu("Modifier la courbe", modMenu);
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
