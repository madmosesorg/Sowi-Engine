/*
 * CalcFPS.cpp
 *
 *  Created on: 15.12.2011
 *      Author: madmoses
 */

#include <GL/glut.h>
#include "CalcFPS.h"
#include <iostream>

using namespace std;

namespace sowi {

CalcFPS::CalcFPS() {
	frame = 0;
	timebase = 0;

}

CalcFPS::~CalcFPS() {
}

void CalcFPS::drawFPS()
{
	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	int fps;
	if (time - timebase > 1000) {
		fps = frame*1000.0/(time-timebase);
	 	timebase = time;
		frame = 0;
		//cout << fps << endl;
	}
}

} /* namespace sowi */
