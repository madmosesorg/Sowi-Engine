/*
 * Plane.cpp
 *
 *  Created on: 15.01.2012
 *      Author: madmoses
 */

#include "Plane.h"
#include "math.h"

namespace sowi {

Plane::Plane() {
	// TODO Auto-generated constructor stub

}

Plane::~Plane() {
	// TODO Auto-generated destructor stub
}

void Plane::setCoefficients(float a, float b, float c, float d) {
	//compute the lenght of the vector
	float l = sqrt(a*a + b*b + c*c);

	this->a = a/l;
	this->b = b/l;
	this->c = c/l;
	this->d = d/l;
}

float Plane::distance(float x, float y, float z)
{
	return this->a * x + this->b * y + this->c * z  + d;
}


} /* namespace sowi */
