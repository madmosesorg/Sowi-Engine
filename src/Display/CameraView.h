/*
 * CameraView.h
 *
 *  Created on: Dec 16, 2011
 *      Author: moses
 */

#ifndef CAMERAVIEW_H_
#define CAMERAVIEW_H_

namespace sowi {

class CameraView {
public:
	CameraView();
	virtual ~CameraView();
	void renderCameraView();
	void toggleMouseWarp();

	//callbcak funktionen
	void changeSize(int w, int h);
	void mousePosition(int x, int y);

	//Getter und Setter für bewegung
	void goFarwardStart();
	void goFarwardStop();
	void goBackwardStart();
	void goBackwardStop();
	void goLeftStart();
	void goLeftStop();
	void goRightStart();
	void goRightStop();

	float mouseDirectionX;
	float mouseDirectionY;

private:
	GLdouble eyeX, eyeY, eyeZ;
	GLdouble centerX, centerY, centerZ;
	int	windowWidth, windowHeight;
	int previousTime;

	//MausBewegung


	//Wie Weit soll pro Zeiteinheit(1000ms) bewegt werden
	float moveforward_backward;
	float moveSiteward;

	//Status Variablen
	bool forward, backward, left, right;

	bool mouseWarp;
};

} /* namespace sowi */
#endif /* CAMERAVIEW_H_ */
