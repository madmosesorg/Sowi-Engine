//============================================================================
// Name        : Sowi.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include "DrawManager.h"

using namespace std;
using namespace sowi;

DrawManager *draw;



void processTimedEvent(int x) {
  // perform light movement and trigger redisplay
    glutPostRedisplay();
    draw->angle += 0.3f;
  // start event again
  glutTimerFunc(10 , processTimedEvent, 0);
}


void processNormalKeys(unsigned char key, int x, int y) {
	draw->processNormalKeys(key, x, y);
}

void releaseNormalKeys(unsigned char key, int x, int y)
{
	draw->releaseNormalKeys(key, x, y);
}

void processSpecialKeys(int key, int x, int y) {


}

void changeSize(int w, int h) {
	draw->changeSize(w,h);
}

void renderScene(void) {
	draw->renderScene();
}


void mousePosition(int x, int y)
{
	draw->mousePosition(x,y);
}



int main(int argc, char **argv) {
	cout << "Try Init Engine" << endl;
	//GLEW INIT
	string s = argv[0];
	size_t found;
	found = s.rfind('/');
	s.erase(found+1, s.size() - found+1);
	// s ist der pfad zur exe datei

	draw = new DrawManager(s);

	draw->initGlut(argc, argv);
	glutReshapeFunc(changeSize);
	glutDisplayFunc(renderScene);


	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutKeyboardUpFunc(releaseNormalKeys);
	glutPassiveMotionFunc(mousePosition);




	glutTimerFunc(20, processTimedEvent, 0);
	glutMainLoop();
	return 0;
}
