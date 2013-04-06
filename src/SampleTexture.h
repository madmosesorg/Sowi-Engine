/*
 * SampleTexture.h
 *
 *  Created on: 16.01.2012
 *      Author: madmoses
 */

#ifndef SAMPLETEXTURE_H_
#define SAMPLETEXTURE_H_
#include <GL/glew.h>
#include <GL/glut.h>
#include "imageloader.h"
#include <string>

using namespace std;


namespace sowi {

class SampleTexture {

private:
	GLuint textureId;

public:
	SampleTexture();
	void render();
	GLuint loadTexture(Image* image);
	virtual ~SampleTexture();
	void init(string path);
};

} /* namespace sowi */
#endif /* SAMPLETEXTURE_H_ */
