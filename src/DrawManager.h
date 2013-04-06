/*
 * DrawManager.h
 *
 *  Created on: 14.12.2011
 *      Author: madmoses
 */

#ifndef DRAWMANAGER_H_
#define DRAWMANAGER_H_
#include <iostream>
#include <string>
#include "Display/CalcFPS.h"
#include "Display/CameraView.h"
#include "Heightmap/RandomHeightmap.h"
#include "Skybox/Skybox.h"
#include "AllRoundObject.h"
#include "Culling/Frustum.h"
#include "SampleTexture.h"

using namespace std;

namespace sowi {

class DrawManager {
public:

	DrawManager(string execpath);
	virtual ~DrawManager();
	void renderScene(void);
	void initGlut(int argc, char **argv);
	float angle;

	//CallBack Funktionen
	void processNormalKeys(unsigned char key, int x, int y);
	void releaseNormalKeys(unsigned char key, int x, int y);
	void changeSize(int w, int h);
	void mousePosition(int x, int y);

private:
	CalcFPS fps;
	CameraView cameraView;
	RandomHeightmap heightmap;
	AllRoundObject *cube;
	Frustum frustum;
	Skybox *skybox;
	SampleTexture sampleTexture;

	string execpath;


	void initLight();

};

} /* namespace sowi */
#endif /* DRAWMANAGER_H_ */
