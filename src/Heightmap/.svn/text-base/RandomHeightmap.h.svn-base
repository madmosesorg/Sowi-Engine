/*
 * RandomHeightmap.h
 *
 *  Created on: Dec 30, 2011
 *      Author: moses
 */

#ifndef RANDOMHEIGHTMAP_H_
#define RANDOMHEIGHTMAP_H_

#include <GL/glut.h>

namespace sowi {

class RandomHeightmap {
public:
	RandomHeightmap(int width, int height);
	void render();
	void initVBO();
	virtual ~RandomHeightmap();



private:
	GLfloat getRandomHeight();
	int width, height;

	struct Vertices
	{
		GLfloat x, y, z;
	};
	Vertices *vertices;
	Vertices *normale;
	Vertices *color;

	struct Faces
	{
		GLuint f1, f2, f3;
	};
	Faces *faces;

	//VBO Pointer
	//ID's of VBO
	GLuint VBOverticesID;
	GLuint VBOindicesID;
	GLuint VBOnormalsID;
	GLuint VBOcolorID;

	void setVertice(int x, int y, Vertices value);
	void setColor(int x, int y, Vertices value);
	RandomHeightmap::Vertices getVertice(int x, int y);
	RandomHeightmap::Vertices getColor(int x, int y);
	RandomHeightmap::Vertices subVertice(Vertices v1, Vertices v2);
	RandomHeightmap::Vertices kreuzVertice(Vertices v1, Vertices v2);
	void faultAlgorithm();
	void printVertices(Vertices v);

};

} /* namespace sowi */
#endif /* RANDOMHEIGHTMAP_H_ */
