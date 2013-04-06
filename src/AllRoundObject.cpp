/*
 * AllRoundObject.cpp
 *
 *  Created on: 13.12.2011
 *      Author: madmoses
 */
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <assimp/assimp.hpp>      // C++ importer interface
#include <assimp/aiScene.h>       // Output data structure
#include <assimp/aiPostProcess.h> // Post processing flags
#include "AllRoundObject.h"
#include "Culling/Frustum.h"

using namespace std;

AllRoundObject::AllRoundObject(const std::string& pFile, sowi::Frustum *frustum) {
	this->frustum = frustum;
	this->pFile = pFile;
	DoTheImportThing();
	inside = 0;
	outside = 0;
	//this->boundingBox = new BoundingBox;
	// Init VBO's



}

AllRoundObject::~AllRoundObject() {
	// TODO Auto-generated destructor stub
}


void AllRoundObject::render(float x, float y, float z)
{

	if(sowi::Frustum::OUTSIDE == ((frustum->pointInFrustum(boundingBox.A.X + x,boundingBox.A.Y + y, boundingBox.A.Z + z)) |
								  (frustum->pointInFrustum(boundingBox.G.X + x,boundingBox.G.Y + y, boundingBox.G.Z + z))))
		outside++;
	//if(sowi::Frustum::OUTSIDE == (frustum->pointInFrustum(boundingBox.A.X,boundingBox.A.Y, boundingBox.A.Z))) outside++;s
	else
	{
		inside++;

		glPushMatrix();
			glTranslatef(x, y, z);
	    glEnableClientState(GL_NORMAL_ARRAY);
	    glEnableClientState(GL_VERTEX_ARRAY);

	    glBindBuffer(GL_ARRAY_BUFFER, VBOnormalsID);
	    glNormalPointer(GL_FLOAT, 0, 0);

	    glBindBuffer(GL_ARRAY_BUFFER, VBOverticesID);
	    glVertexPointer(3, GL_FLOAT, 0, 0);

	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindicesID);
		glDrawElements(GL_TRIANGLES, this->numFaces*3, GL_UNSIGNED_INT, 0);

	    glDisableClientState(GL_VERTEX_ARRAY);
	    glDisableClientState(GL_NORMAL_ARRAY);
		glPopMatrix();
	}
}

void AllRoundObject::render()
{

}


int AllRoundObject::getInside() const
{
    return inside;
}

int AllRoundObject::getOutside() const
{
    return outside;
}

void AllRoundObject::setInside(int inside)
{
    this->inside = inside;
}

void AllRoundObject::setOutside(int outside)
{
    this->outside = outside;
}

void AllRoundObject::DoTheImportThing()
{
  // Create an instance of the Importer class
  Assimp::Importer importer;

  // And have it read the given file with some example postprocessing
  // Usually - if speed is not the most important aspect for you - you'll
  // propably to request more postprocessing than we do in this example.
  scene = importer.ReadFile( this->pFile,
        aiProcess_CalcTangentSpace       |
        aiProcess_Triangulate            |
        aiProcess_JoinIdenticalVertices  | aiProcess_FlipWindingOrder |
        aiProcess_SortByPType);

  cout << "Load " << this->pFile << " ";
  // If the import failed, report it
  if( !scene)
  {
    cout << ( importer.GetErrorString())<< endl;
  }
  else
  {
	  cout << "SUCCESSFUL" << endl;
  }


  	  aiMesh** meshes = scene->mMeshes;

  	  numVertices = 0;
  	  numFaces = 0;
  	  unsigned int start_index = 0;
  	  unsigned int start_index_faces = 0;
  	  unsigned int old_faces = 0;
  	  cout << "Anzahl Meshes: " << scene->mNumMeshes << endl;


  	  for(unsigned int nMeshes = 0; nMeshes < scene->mNumMeshes; nMeshes++)
  	  {
  		  numVertices +=meshes[nMeshes]->mNumVertices;
  		  numFaces += meshes[nMeshes]->mNumFaces;

  	  }
  	  cout << numFaces << " " << numVertices << endl;
  	  //Für jedes Mesh die Vertices und Faces kopieren
  	  this->vertices = new Vertices[numVertices];
  	  this->normales = new Vertices[numVertices];
  	  this->faces = new Faces[numFaces];
  	  GLfloat min_x = 0, max_x = 0,
  	  	  	  min_y = 0, max_y = 0,
  	  	  	  min_z = 0, max_z = 0;

  	  for(unsigned int nMeshes = 0; nMeshes < scene->mNumMeshes; nMeshes++)
  	  {
  		  cout << "Mesh: " << nMeshes << endl;
  		  //Alles Vertices Kopieren in meine Struktur
  		  for(unsigned int nVertex = 0; nVertex < meshes[nMeshes]->mNumVertices; nVertex++)
  		  {
  			vertices[start_index].X = meshes[nMeshes]->mVertices[nVertex].x;
  			vertices[start_index].Y = meshes[nMeshes]->mVertices[nVertex].y;
  			vertices[start_index].Z = meshes[nMeshes]->mVertices[nVertex].z;
  			if(meshes[nMeshes]->mVertices[nVertex].x< min_x) min_x = meshes[nMeshes]->mVertices[nVertex].x;
  			if(meshes[nMeshes]->mVertices[nVertex].y< min_y) min_y = meshes[nMeshes]->mVertices[nVertex].y;
  			if(meshes[nMeshes]->mVertices[nVertex].z< min_z) min_z = meshes[nMeshes]->mVertices[nVertex].z;

  			if(meshes[nMeshes]->mVertices[nVertex].x > max_x) max_x = meshes[nMeshes]->mVertices[nVertex].x;
  			if(meshes[nMeshes]->mVertices[nVertex].y > max_y) max_y = meshes[nMeshes]->mVertices[nVertex].y;
  			if(meshes[nMeshes]->mVertices[nVertex].z > max_z) max_z = meshes[nMeshes]->mVertices[nVertex].z;

  			normales[start_index].X = meshes[nMeshes]->mNormals[nVertex].x;
  			normales[start_index].Y = meshes[nMeshes]->mNormals[nVertex].y;
  			normales[start_index].Z = meshes[nMeshes]->mNormals[nVertex].z;
  			start_index++;
  		  }
  		  //cout << "############## FACES ################" << endl;
  		  for(unsigned int nFaces = 0;  nFaces < meshes[nMeshes]->mNumFaces; nFaces++)
  		  {
  			  //cout << meshes[nMeshes]->mFaces[nFaces].mIndices[0] << " " <<  endl;
  			  faces[start_index_faces].X = meshes[nMeshes]->mFaces[nFaces].mIndices[0] + old_faces;
  			  faces[start_index_faces].Y = meshes[nMeshes]->mFaces[nFaces].mIndices[1] + old_faces;
  			  faces[start_index_faces].Z = meshes[nMeshes]->mFaces[nFaces].mIndices[2] + old_faces;
  			  start_index_faces++;
  		  }
  		  old_faces = start_index;
  	  }
  	 boundingBox.A = {min_x, min_y, max_z};
  	 boundingBox.B = {max_x, min_y, max_z};
  	 boundingBox.C = {max_x, min_y, min_z};
  	 boundingBox.D = {min_x, min_y, min_z};

  	 boundingBox.E = {min_x, max_y, max_z};
  	 boundingBox.F = {max_x, max_y, max_z};
  	 boundingBox.G = {max_x, max_y, min_z};
  	 boundingBox.H = {min_x, max_y, min_z};


 	cout << "Load VBO's ";

 	glGenBuffers(1, &VBOverticesID);
 	glGenBuffers(1, &VBOindicesID);
 	glGenBuffers(1, &VBOnormalsID);
   	glGenBuffers(1, &VBOcolorID);
  	 //Load VBO in Mem
     //bind VBO in order to use
     glBindBuffer(GL_ARRAY_BUFFER, VBOverticesID);
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindicesID);

     // upload data to VBO
     glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) * this->numVertices, vertices, GL_STATIC_DRAW);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Faces)* this->numFaces, faces, GL_STATIC_DRAW);

     //Normalesn hochladen
     glBindBuffer(GL_ARRAY_BUFFER, VBOnormalsID);
     glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) * numVertices, normales, GL_STATIC_DRAW);
}
















