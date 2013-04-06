/*
 * Plane.h
 *
 *  Created on: 15.01.2012
 *      Author: madmoses
 */

#ifndef PLANE_H_
#define PLANE_H_

namespace sowi {

class Plane {

private:
	float a,b,c,d, length;
public:

	Plane();
	virtual ~Plane();
	void setCoefficients(float a, float b, float c, float d);
	float distance(float x, float y, float z);
};

} /* namespace sowi */
#endif /* PLANE_H_ */
