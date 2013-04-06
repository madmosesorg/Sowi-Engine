/*
 * Skybox.h
 *
 *  Created on: 11.01.2012
 *      Author: madmoses
 */

#ifndef SKYBOX_H_
#define SKYBOX_H_
#include "GL/glut.h"
#include "../Display/CameraView.h"
#include <string>

using namespace std;

namespace sowi {

class Skybox {
private:
	GLuint textureId[6];
	CameraView *cameraView;

public:
	Skybox(CameraView *cameraView);
	void init(string path);
	void render();
	virtual ~Skybox();
};

} /* namespace sowi */
#endif /* SKYBOX_H_ */
