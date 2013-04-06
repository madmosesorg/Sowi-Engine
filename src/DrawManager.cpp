/*
 * DrawManager.cpp
 *
 *  Created on: 14.12.2011
 *      Author: madmoses
 */
#include <GL/glew.h>
#include <GL/glut.h>
#include "Display/CalcFPS.h"
#include "Display/CameraView.h"
#include "AllRoundObject.h"
#include <iostream>
#include "Heightmap/RandomHeightmap.h"
#include "DrawManager.h"
#include "Skybox/Skybox.h"
#include <string>
#include "Culling/Frustum.h"
#include "SampleTexture.h"

using namespace std;

namespace sowi {



DrawManager::DrawManager(string execpath) : fps(), cameraView(), heightmap(500,500), frustum() {
	this->execpath = execpath;
	angle  = 0.0f;
	cout << "FINISH" << endl;

}

DrawManager::~DrawManager() {
	// TODO Auto-generated destructor stub
}

/* Initialisiert alle Gluteigendschaften
 *
 */
void DrawManager::initGlut(int argc, char **argv)
{
	// init GLUT and create Window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(700,500);
	glutCreateWindow("Test Engine");

	  GLenum err = glewInit();
	  if (GLEW_OK != err) cout << "GLEW Error (" << err << "): " << glewGetErrorString(err) << endl;
	  cout << "GLEW Version: " << glewGetString(GLEW_VERSION) << endl;
	  // check if VBOs are supported
	  if(glGenBuffers && glBindBuffer && glBufferData && glBufferSubData &&
	    glMapBuffer && glUnmapBuffer && glDeleteBuffers && glGetBufferParameteriv) {
	      cout << "VBOs are supported!" << endl;
	  }
	  else {
	    cout << "VBOs are NOT supported!" << endl;
	    exit(1);
	  }

	glEnable(GL_DEPTH_TEST);
	initLight();
	heightmap.initVBO();
	skybox = new Skybox(&cameraView);
	skybox->init(execpath);
	cube = new AllRoundObject(execpath + "../models/kaktus.3ds", &frustum);
	sampleTexture.init(execpath);
}

void DrawManager::initLight()
{
	 glEnable(GL_DEPTH_TEST);
	  // set shading model
	  glShadeModel(GL_SMOOTH);
	  // set lighting and material
	  GLfloat global_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	  GLfloat ambientLight[] =   { 0.1f, 0.1f, 0.1f, 1.0f };
	  GLfloat diffuseLight[] =   { 1.0f, 1.0f, 1.0f, 1.0f };
	  GLfloat specularLight[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
	  GLfloat shininess = 128.0f;
	  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	  glLightf(GL_LIGHT0, GL_SHININESS, shininess);
	  glEnable(GL_LIGHT0);


	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);


}

void DrawManager::releaseNormalKeys(unsigned char key, int x, int y)
{
	switch(key)
		{
		case 'w':
			cameraView.goFarwardStop();
			break;

		case 's':
			cameraView.goBackwardStop();
			break;

		case 'a':
			cameraView.goLeftStop();
			break;

		case 'd':
			cameraView.goRightStop();
			break;

		case 27:
			exit(0);
			break;

		}
}
void DrawManager::processNormalKeys(unsigned char key, int x, int y)
{
	switch(key)
		{
		case 'w':
			cameraView.goFarwardStart();
			break;

		case 's':
			cameraView.goBackwardStart();
			break;

		case 'a':
			cameraView.goLeftStart();
			break;

		case 'd':
			cameraView.goRightStart();
			break;

		case 'p':
			cameraView.toggleMouseWarp();
			break;

		case 27:
			exit(0);
			break;

		}
}

void DrawManager::changeSize(int w, int h)
{
	cameraView.changeSize(w,h);
}

void DrawManager::mousePosition(int x, int y)
{
	cameraView.mousePosition(x,y);
}

void DrawManager::renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations


	// Set the camera
	skybox->render();
	cameraView.renderCameraView();

	//Nachdem die Kamera Positioniert wurde kann das Frustum berechner werden, sollte
	//an der Stelle optimiert werden, weil muss nur berechnet werden wenn sich der
	//Kamera Blickwinkel ändert

	bool once = false;
	if(!once)
		frustum.updateFrustum();
	once = true;

	frustum.render();

	  static GLfloat lp[] = { 10, 10, 20, 1.0f };

	  // draw yellow sphere for light source
	  static GLfloat test = 0;
	  test += 1.0f;
	  glPushMatrix();
	  	  glDisable(GL_LIGHTING);
	  	  glRotatef(test,0,1,0);
	  	  glLightfv(GL_LIGHT0, GL_POSITION, lp);
	  	  glTranslatef(lp[0], lp[1], lp[2]);
	  	  glColor3f(1,1,0);
	  	  glutSolidSphere(0.2f,16,16);

	  	  glEnable(GL_LIGHTING);
	  glPopMatrix();

	  sampleTexture.render();
	heightmap.render();


	cube->setInside(0);
	cube->setOutside(0);
	glColor3f(0.0f, 0.42f, 0.0f);
	for(int i = 0;i < 8;i++)
		for(int j = 0;j < 8;j++)
			cube->render(30*i,0,30*j);
	//cout << "Gesehen: " << cube->getInside() << " Nicht gesehen: " << cube->getOutside() << endl;

	glutSwapBuffers();
	fps.drawFPS();
}

} /* namespace sowi */
