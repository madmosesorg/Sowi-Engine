/*
 * CameraView.cpp
 *
 *  Created on: Dec 16, 2011
 *      Author: moses
 */
#define PI 3.14159265

#include <GL/glut.h>
#include "CameraView.h"
#include <iostream>
#include <math.h>


using namespace std;

namespace sowi {



	CameraView::CameraView() {
		forward = false;
		backward = false;
		left = false;
		right = false;
		previousTime = 0;
		moveforward_backward = 50.0f;
		moveSiteward = 30.0f;
		//Gibt die Position des Betrachters an.
		eyeX = 0.0f;
		eyeY = 1.85f;
		eyeZ = 3.0f;
		//centerX, centerY, centerZ 	Gibt die Position des Refernenzpunktes an, auf den "geblickt" wird.
		centerX = 0.0f;
		centerY = 0.0f;
		centerZ = 0.0f;
		//upX, upY, upZ 	Gibt die Richtung des Vektors an, der nach oben zeigt.
		mouseDirectionX = 0;
		mouseDirectionY = 0;

		mouseWarp = true;
	}

	CameraView::~CameraView() {
		// TODO Auto-generated destructor stub
	}

	void CameraView::changeSize(int w, int h)
	{
		this->windowHeight = w;
		this->windowWidth = h;
		// Prevent a divide by zero, when window is too short
		// (you cant make a window of zero width).
		if(h == 0)
			h = 1;
		float ratio = 1.0* w / h;

		// Use the Projection Matrix
		glMatrixMode(GL_PROJECTION);

	        // Reset Matrix
		glLoadIdentity();

		// Set the viewport to be the entire window
		glViewport(0, 0, w, h);

		// Set the correct perspective.
		gluPerspective(45,ratio,1,1000);

		// Get Back to the Modelview
		glMatrixMode(GL_MODELVIEW);
	}


	void CameraView::mousePosition(int x, int y)
	{
		if(mouseWarp)
		{
			mouseDirectionX -= (x - this->windowWidth/2) * 0.1f;
			mouseDirectionY += (y - this->windowHeight/2) * 0.1f;
			if(mouseDirectionY > 180) mouseDirectionY = 180;
			else if(mouseDirectionY < 0) mouseDirectionY = 0;
		}
	}

	void CameraView::renderCameraView()
	{

	    int currentTime = glutGet(GLUT_ELAPSED_TIME);
	    int timeInterval = currentTime - previousTime;

	    //Berechne Blickrichtung
	    GLdouble tmpEyeX, tmpEyeY, tmpEyeZ;

	    tmpEyeX = sin(mouseDirectionY*PI/180)*sin(mouseDirectionX*PI/180);
	    tmpEyeZ = sin(mouseDirectionY*PI/180)*cos(mouseDirectionX*PI/180);
	    tmpEyeY = cos(mouseDirectionY*PI/180);

	    //Bewegung Berechnen
	    if(forward)
	    {
	    	eyeX += timeInterval * tmpEyeX / 10;
	    	eyeY += timeInterval * tmpEyeY / 10;
	    	eyeZ += timeInterval * tmpEyeZ / 10;
	    }
	    if(backward)
	    {
	    	eyeZ -= timeInterval * tmpEyeZ / 10;
	    	eyeY -= timeInterval * tmpEyeY / 10;
	    	eyeX -= timeInterval * tmpEyeX / 10;
	    }
	    if(left)
	    {
	    	eyeX += timeInterval * sin((mouseDirectionX+90)*PI/180) / 10;
	    	eyeZ += timeInterval * cos((mouseDirectionX+90)*PI/180) / 10;
	    }
	    if(right)
	    {
	    	eyeX -= timeInterval * sin((mouseDirectionX+90)*PI/180) / 10;
	    	eyeZ -= timeInterval * cos((mouseDirectionX+90)*PI/180) / 10;
	    }

	    //Mausbewegung =>

	    previousTime = currentTime;

	    glLoadIdentity();
/*
		glPushMatrix();
		glDepthMask(false);
	    glPushAttrib(GL_ENABLE_BIT);
	    glEnable(GL_TEXTURE_2D);

	    glDisable(GL_DEPTH_TEST);
	    glDisable(GL_LIGHTING);
	    glDisable(GL_BLEND);

	    glRotatef(mouseDirectionX, 0, 1, 0);
		glBegin(GL_QUADS);
				glColor3f(1,1,1);
		        glVertex3f(  5.0f, -5.0f, -5.0f );
		        glColor3f(1,0,0);
		        glVertex3f( -5, -5, -5 );
		        glVertex3f( -5,  5, -5 );
		        glVertex3f(  5,  5, -5 );
		glEnd();

		glPopAttrib();
		glPopMatrix();
	    glEnable( GL_DEPTH_TEST );
		glDepthMask(true);


*/


		gluLookAt(	eyeX, eyeY, eyeZ,
					eyeX + tmpEyeX, eyeY + tmpEyeY, eyeZ + tmpEyeZ ,
					0.0f, 10.0f,  0.0f);


		//Maus wieder in die mitte Positionieren
		if(mouseWarp)
			glutWarpPointer(this->windowWidth / 2, this->windowHeight / 2);
	}


	//Getter und Setter

	void CameraView::toggleMouseWarp()
	{
		mouseWarp = !mouseWarp;
	}
	void CameraView::goFarwardStart()
	{
		forward = true;
	}

	void CameraView::goFarwardStop()
	{
		forward = false;
	}

	void CameraView::goBackwardStart()
	{
		backward = true;
	}

	void CameraView::goBackwardStop()
	{
		backward = false;
	}

	void CameraView::goLeftStart()
	{
		left = true;
	}

	void CameraView::goLeftStop()
	{
		left = false;

	}

	void CameraView::goRightStart()
	{
		right = true;
	}

	void CameraView::goRightStop()
	{
		right = false;
	}
} /* namespace sowi */
















