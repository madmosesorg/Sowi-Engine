/*
 * Skybox.cpp
 *
 *  Created on: 11.01.2012
 *      Author: madmoses
 */

#include "Skybox.h"
#include "GL/glut.h"
#include "../imageloader.h"
#include <iostream>
#include "../Display/CameraView.h"
#include <string>

using namespace std;

namespace sowi {


void Skybox::render() {
	glLoadIdentity();
	glDepthMask(false);
	glRotatef(cameraView->mouseDirectionY-90,1,0,0);
	glRotatef(cameraView->mouseDirectionX / -1,0,1,0);

	glScalef(50.0,50.0,50.0);
	glDepthMask(false);
    glPushAttrib(GL_ENABLE_BIT);
    glEnable(GL_TEXTURE_2D);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
	glClear(GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, textureId[0]);
	glColor3f(1.0,1.0,1.0);

	glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
    glTexCoord2f(1, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
    glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
    glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
	glEnd();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, textureId[1]);
	//glColor3f(0,1.0,0);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
        glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f, -0.5f );
        glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
    glEnd();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, textureId[2]);
    //glColor3f(0.7,0.7,1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
        glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f,  0.5f );
    glEnd();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, textureId[3]);
    glColor3f(1.0,1.0,1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
        glTexCoord2f(1, 0); glVertex3f( -0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f,  0.5f );
        glTexCoord2f(0, 1); glVertex3f( -0.5f,  0.5f, -0.5f );
    glEnd();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, textureId[4]);


    glBegin(GL_QUADS);
        glTexCoord2f(1, 0); glVertex3f( -0.5f,  0.5f, -0.5f );
        glTexCoord2f(1, 1); glVertex3f( -0.5f,  0.5f,  0.5f );
        glTexCoord2f(0, 1); glVertex3f(  0.5f,  0.5f,  0.5f );
        glTexCoord2f(0, 0); glVertex3f(  0.5f,  0.5f, -0.5f );
    glEnd();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, textureId[5]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -0.5f, -0.5f, -0.5f );
        glTexCoord2f(0, 1); glVertex3f( -0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 1); glVertex3f(  0.5f, -0.5f,  0.5f );
        glTexCoord2f(1, 0); glVertex3f(  0.5f, -0.5f, -0.5f );
    glEnd();

	glDisable(GL_TEXTURE_2D);
	glDepthMask(true);
	glPopMatrix();
	glPopAttrib();
    glEnable( GL_DEPTH_TEST );
	glDepthMask(true);
}


GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	cout << "geklappt "<< endl;
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	cout << "width" << image->width << " height " << image->height << endl;
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void Skybox::init(string path)
{
	Image* image1 = loadBMP((path + "../skybox/neg_x.bmp").c_str());
	textureId[0] = loadTexture(image1);
	Image* image2 = loadBMP((path + "../skybox/neg_z.bmp").c_str());
	textureId[1] = loadTexture(image2);
	Image* image3 = loadBMP((path + "../skybox/pos_x.bmp").c_str());
	textureId[2] = loadTexture(image3);
	Image* image4 = loadBMP((path + "../skybox/pos_z.bmp").c_str());
	textureId[3] = loadTexture(image4);
	Image* image5 = loadBMP((path + "../skybox/pos_y.bmp").c_str());
	textureId[4] = loadTexture(image5);
	Image* image6 = loadBMP((path + "../skybox/neg_y.bmp").c_str());
	textureId[5] = loadTexture(image6);
	delete image1;
	delete image2;
	delete image3;
	delete image4;
	delete image5;
	delete image6;
}

Skybox::Skybox(CameraView *cameraView) {
	this->cameraView = cameraView;
}

Skybox::~Skybox() {
	// TODO Auto-generated destructor stub
}

} /* namespace sowi */
