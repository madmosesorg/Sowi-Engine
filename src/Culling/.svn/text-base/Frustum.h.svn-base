/*
 * Frustum.h
 *
 *  Created on: 15.01.2012
 *      Author: madmoses
 */

#ifndef FRUSTUM_H_
#define FRUSTUM_H_
#include "Plane.h"


namespace sowi {

class Frustum {

private:
	enum {
		TOP = 0, BOTTOM = 1, LEFT = 2,
		RIGHT = 3, NEARP = 4, FARP = 5
	};

	Plane pl[6];

public:
	enum Position{OUTSIDE = 0, INTERSECT, INSIDE};
	Frustum();
	virtual ~Frustum();
	void multMat2(float *res, float *a, float *b);
	void updateFrustum();
	void setFrustum(float *m);
	void render();
	int pointInFrustum(float x, float y, float z);
};

} /* namespace sowi */
#endif /* FRUSTUM_H_ */
