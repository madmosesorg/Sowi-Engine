/*
 * RandomHeightmap.cpp
 *
 *  Created on: Dec 30, 2011
 *      Author: moses
 */
#include <cstdlib>
#include <ctime>
#include <iostream>
//#include <GL/glut.h>
#include <GL/glew.h>

#include "RandomHeightmap.h"
#include <math.h>
#define PI 3.14159265

using namespace std;

namespace sowi {



RandomHeightmap::RandomHeightmap(int width, int height) {
	this->width = width;
	this->height = height;
	this->vertices = new Vertices[width*height];
	this->color = new Vertices[width*height];
	this->normale = new Vertices[width*height];
	this->faces = new Faces[(width-1)*(height-1)*2];

	for(int i = 0;i<width*height;i++)
	{
		this->normale[i].x = 0;
		this->normale[i].y = 0;
		this->normale[i].z = 0;
	}

	//Erstelle DES!
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<height;j++)
		{
			Vertices v = {i*2.0,0,j*2.0};
			setVertice(i,j,v);
		}
	}
	//Berechne The Fault Algorithm
	for(int i=0;i<400;i++)
	{
		faultAlgorithm();
	}

	//Berechne Color
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<height;j++)
		{
			Vertices v = getVertice(i,j);
			Vertices c;
			if(v.y < -150)
			{
				c.x = 0;
				c.y = 0;
				c.z = 1.0;
				setColor(i,j,c);
			}
			else if(v.y < -140)
			{
				c.x = 0.9;
				c.y = 1.0;
				c.z = 0;
				setColor(i,j,c);
			}
			else if(v.y < -65)
			{
				c.x = 0;
				c.y = 1.0;
				c.z = 0;
				setColor(i,j,c);
			}
			else if(v.y < 2)
			{
				c.x = 0.0;
				c.y = .33;
				c.z = 0;
				setColor(i,j,c);
			}
			else if(v.y < 20)
			{
				c.x = 0.370;
				c.y = 0.370;
				c.z = 0.370;
				setColor(i,j,c);
			}
			else
			{
				c.x = 1.0;
				c.y = 1.0;
				c.z = 1.0;
				setColor(i,j,c);
			}
		}
	}
	int index = 0;
	//Berechne Faces
	for(int i = 0;i<this->width-1;i++)
	{
		for(int j=0;j<height-1;j++)
		{
			this->faces[index].f1 = this->width * j + i;
			this->faces[index].f2 = this->width * j + (i+1);
			this->faces[index].f3 = this->width * (j+1) + i;
			index++;
			this->faces[index].f1 = this->width * i + (j+1);
			this->faces[index].f2 = this->width * (i+1) + (j+1);
			this->faces[index].f3 = this->width * (i+1) + j;
			index++;

		}
	}
	//Berechne Normale
	for(int i = 0;i<(width-1)*(height-1)*2;i++)
	{
		Faces f = this->faces[i];
		Vertices v1 = this->vertices[f.f1];
		Vertices v2 = this->vertices[f.f2];
		Vertices v3 = this->vertices[f.f3];
		//cout << "VERTICES TO CALC FOR NORMALS" << endl;
		//printVertices(v1);
		//printVertices(v2);
		//printVertices(v3);
		//cout << "Vertices after sub"<< endl;
		Vertices v1_v2 = subVertice(v1, v2);
		Vertices v2_v3 = subVertice(v2, v3);
		//printVertices(v1_v2);
		//printVertices(v2_v3);
		// v1-v2 x v2-v3
		//cout << "Berechnete Normale" << endl;
		Vertices kreuz = kreuzVertice(v1_v2, v2_v3);
		//printVertices(kreuz);
		this->normale[f.f1].x += kreuz.x;
		this->normale[f.f1].y += kreuz.y;
		this->normale[f.f1].z += kreuz.z;

		this->normale[f.f2].x += kreuz.x;
		this->normale[f.f2].y += kreuz.y;
		this->normale[f.f2].z += kreuz.z;

		this->normale[f.f3].x += kreuz.x;
		this->normale[f.f3].y += kreuz.y;
		this->normale[f.f3].z += kreuz.z;

	}
	cout << "NORMALISIEREN" << endl;
	//Vektoren Normalisieren
	for(int i = 0;i<width*height;i++)
	{
		Vertices v = this->normale[i];
		GLfloat sum = -1 * sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
		normale[i].x = normale[i].x / sum;
		normale[i].y = normale[i].y / sum;
		normale[i].z = normale[i].z / sum;
		//cout << "normale:" << normale[i].x << " " << normale[i].y << " " << normale[i].z << endl;
	}


}

void RandomHeightmap::initVBO()
{

	cout << "Load VBO's ";

	glGenBuffers(1, &VBOverticesID);
	glGenBuffers(1, &VBOindicesID);
	glGenBuffers(1, &VBOnormalsID);
	glGenBuffers(1, &VBOcolorID);

    //bind VBO in order to use
    glBindBuffer(GL_ARRAY_BUFFER, VBOverticesID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindicesID);

    // upload data to VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) * width*height, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Faces)*(width-1)*(height-1)*2, faces, GL_STATIC_DRAW);

    //Normalesn hochladen
    glBindBuffer(GL_ARRAY_BUFFER, VBOnormalsID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) * width*height, normale, GL_STATIC_DRAW);

    //Farben hochladen
    glBindBuffer(GL_ARRAY_BUFFER, VBOcolorID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices) * width*height, color, GL_STATIC_DRAW);
	cout << "OK" << endl;
}

void RandomHeightmap::faultAlgorithm()
{
	int x1, x2, y1, y2;
	x1 = (int) getRandomHeight() * 11% this->width;
	y1 = (int)getRandomHeight() *3 % this->height;
	x2 = (int)getRandomHeight() % this->width;
	y2 = (int)getRandomHeight() * 7% this->height;
	//Gerade
	int gx = x2 - x1;
	int gy = y2 - y1;
	static float breite = 15000;
	breite -= 20.5;
	float dist;
	static float faktor = 2.5;
	//faktor += 0.0001f;
	if(faktor < 2.8) faktor = 2.8;
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<height;j++)
		{
		Vertices v = getVertice(i,j);
		dist = gx * (4 - j) - gy * (i - x1);

		if(fabs(dist) < breite)
		{
			v.y += (0.8 + cos(PI * dist / breite)) * faktor;
		}
		else if(dist <= 0)
		{
			v.y -= (faktor * 0.2);
		}
		else
		{
			v.y -= (faktor * 0.2);
		}
		setVertice(i,j,v);
		//cout << "Dist: " << dist << endl;
		//cout << "Zufallspunkte "<< x1 << " "<< x2 << " " << y1 << " " << y2 << endl;
		//cout << "gerade " << gx << " " << gy << endl;
		}
	}
}
RandomHeightmap::Vertices RandomHeightmap::getVertice(int x, int y)
{
	return this->vertices[this->width * y + x];
}

RandomHeightmap::Vertices RandomHeightmap::getColor(int x, int y)
{
	return this->color[this->width * y + x];
}

RandomHeightmap::Vertices RandomHeightmap::subVertice(Vertices v1, Vertices v2)
{
	Vertices v = {v1.x-v2.x, v1.y-v2.y, v1.z-v2.z};
	return v;
}

RandomHeightmap::Vertices RandomHeightmap::kreuzVertice(Vertices v1, Vertices v2)
{
	Vertices v =
	{
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
	};
	return v;
}

void RandomHeightmap::printVertices(Vertices v)
{
	cout << "Vertices: " << v.x << " " << v.y << " " << v.z << endl;
}

void RandomHeightmap::setVertice(int x, int y, Vertices value)
{
	vertices[y * this->width + x] = value;
}

void RandomHeightmap::setColor(int x, int y, Vertices value)
{
	color[y * this->width + x] = value;
}

RandomHeightmap::~RandomHeightmap() {
}

GLfloat RandomHeightmap::getRandomHeight()
{
	static int random_integer = 0;
	if(!random_integer) srand((unsigned)time(0));
	random_integer = rand();
	GLfloat height = (float) random_integer;
	return height;
}

void RandomHeightmap::render()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, VBOverticesID);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOnormalsID);
    glNormalPointer(GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOcolorID);
    glColorPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBOindicesID);
	glDrawElements(GL_TRIANGLES, (width-1)*(height-1)*6, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
/*

	glBegin(GL_TRIANGLES);

		for(int i = 0;i<(width-1)*(height-1)*2;i++)
		{
			Faces f = this->faces[i];
			Vertices v = this->vertices[f.f1];
			Vertices c = this->color[f.f1];
			Vertices n = this->normale[f.f1];
			glColor3f(c.x, c.y, c.z);
			glNormal3f(n.x, n.y, n.z);
			//cout << "normale:" << n.x << " " << n.y << " " << n.z << endl;

			glVertex3f(v.x, v.y, v.z);
			v = this->vertices[f.f2];
			n = this->normale[f.f2];
			c = this->color[f.f2];
			glColor3f(c.x, c.y, c.z);
			glNormal3f(n.x, n.y, n.z);
			glVertex3f(v.x, v.y, v.z);
			v = this->vertices[f.f3];
			n = this->normale[f.f3];
			c = this->color[f.f3];
			glColor3f(c.x, c.y, c.z);
			glNormal3f(n.x, n.y, n.z);
			glVertex3f(v.x, v.y, v.z);
		}
	glEnd();
*/
}

}















