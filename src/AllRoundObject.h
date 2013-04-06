/*
 * AllRoundObject.h
 *
 *  Created on: 13.12.2011
 *      Author: madmoses
 */

#ifndef ALLROUNDOBJECT_H_
#define ALLROUNDOBJECT_H_
#include <GL/glew.h>
#include <GL/glut.h>
#include "Culling/Frustum.h"
#include <assimp/assimp.hpp>      // C++ importer interface
#include <assimp/aiScene.h>       // Output data structure
#include <assimp/aiPostProcess.h> // Post processing flags







class AllRoundObject {
public:
	const aiScene* scene;

	void render();
	void render(float x, float y, float z);

	AllRoundObject(const std::string& pFile, sowi::Frustum *frustum);
	virtual ~AllRoundObject();
    int getInside() const;
    int getOutside() const;
    void setInside(int inside);
    void setOutside(int outside);

private:
	//AuswertungsVariablen für culling
	int inside;
	int outside;
	std::string pFile;
	sowi::Frustum *frustum;
	void DoTheImportThing();

	unsigned int numVertices;
	unsigned int numFaces;

	//ID's of VBO
	GLuint VBOverticesID;
	GLuint VBOindicesID;
	GLuint VBOnormalsID;
	GLuint VBOcolorID;

	struct Vertices{
		float X;
		float Y;
		float Z;
	};


	struct  Faces{
		unsigned int X;
		unsigned int Y;
		unsigned int Z;
	};

	struct BoundingBox {
		Vertices A,B,C,D,E,F,G,H;

	};

	Vertices *vertices;
	Vertices *normales;
	Faces *faces;
	BoundingBox boundingBox;
};

#endif /* ALLROUNDOBJECT_H_ */
