/*
 * SampleTexture.cpp
 *
 *  Created on: 16.01.2012
 *      Author: madmoses
 */

#include "SampleTexture.h"
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "imageloader.h"
#include <string>
#include <math.h>

using namespace std;

namespace sowi {

SampleTexture::SampleTexture() {

}

SampleTexture::~SampleTexture() {
	// TODO Auto-generated destructor stub
}

GLuint SampleTexture::loadTexture(Image* image) {
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

void SampleTexture::init(string path)
{
	Image* image = loadBMP((path + "../textures/soilcracked.bmp").c_str());
	textureId = loadTexture(image);
	delete image;
}

float calcu(float x, float y, float z)
{
	float erg = (1/2*M_PI) * atan2(x,z) + 0.5;
	//cout << "u " << erg << endl;
	return erg;
}

float calcv(float x, float y, float z)
{
	float erg = (1/M_PI) * asin(y / sqrt(x*x+y*y+z*z)) + 0.5;
	//cout << erg << endl;
	return erg;
}

void SampleTexture::render()
{
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBegin(GL_TRIANGLES);
		glTexCoord2f(calcu(7,3,5), calcv(7,3,5));
		glVertex3f(7,3,5);
		glTexCoord2f(calcu(2,11,7), calcv(2,11,7));
		glVertex3f(2,11,7);
		glTexCoord2f(calcu(11,1,5), calcv(11,1,5));
		glVertex3f(11,1,5);

		glTexCoord2f(1, 0);
		glVertex3f(0,10,0);
		glTexCoord2f(1, 1);
		glVertex3f(10,10,0);
		glTexCoord2f(0, 1);
		glVertex3f(10,0,0);

		//Sphere Mapping

	glEnd();
	glDisable(GL_TEXTURE_2D);
}

} /* namespace sowi */
