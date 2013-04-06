/*
 * Frustum.cpp
 *
 *  Created on: 15.01.2012
 *      Author: madmoses
 */

#include "Frustum.h"
#include <GL/glut.h>
#include <iostream>
#include "Plane.h"

using namespace std;

namespace sowi {

Frustum::Frustum() {
	for(int i = 0;i<6;i++) pl[i] = Plane();

}

Frustum::~Frustum() {
	// TODO Auto-generated destructor stub
}

void Frustum::multMat2(float *res, float *a, float *b) {

	glPushMatrix();

	glLoadMatrixf(b);
	glMultMatrixf(a);
	glGetFloatv(GL_MODELVIEW_MATRIX, res);

	glPopMatrix();
}

int Frustum::pointInFrustum(float x, float y, float z) {

	int result = INSIDE;

	for(int i=0; i < 6; i++) {
		if (pl[i].distance(x,y,z) < 0)
			return OUTSIDE;
	}
	return(result);
}

void Frustum::render()
{
}

#define m(row,col)  m[col*4+row-5]
void Frustum::updateFrustum()
{
	float m[16],p[16], mp[16];

	glGetFloatv(GL_PROJECTION_MATRIX,p);
	glGetFloatv(GL_MODELVIEW_MATRIX,m);

	multMat2(mp, m, p);

	setFrustum(mp);

}

#define m(row,col)  m[col*4+row-5]

void Frustum::setFrustum(float *m) {

	pl[NEARP].setCoefficients(
				 m(3,1) + m(4,1),
				 m(3,2) + m(4,2),
				 m(3,3) + m(4,3),
				 m(3,4) + m(4,4));
	pl[FARP].setCoefficients(
				-m(3,1) + m(4,1),
				-m(3,2) + m(4,2),
				-m(3,3) + m(4,3),
				-m(3,4) + m(4,4));
	pl[BOTTOM].setCoefficients(
				 m(2,1) + m(4,1),
				 m(2,2) + m(4,2),
				 m(2,3) + m(4,3),
				 m(2,4) + m(4,4));
	pl[TOP].setCoefficients(
				-m(2,1) + m(4,1),
				-m(2,2) + m(4,2),
				-m(2,3) + m(4,3),
				-m(2,4) + m(4,4));
	pl[LEFT].setCoefficients(
				 m(1,1) + m(4,1),
				 m(1,2) + m(4,2),
				 m(1,3) + m(4,3),
				 m(1,4) + m(4,4));
	pl[RIGHT].setCoefficients(
				-m(1,1) + m(4,1),
				-m(1,2) + m(4,2),
				-m(1,3) + m(4,3),
				-m(1,4) + m(4,4));
}

#undef M
} /* namespace sowi */












