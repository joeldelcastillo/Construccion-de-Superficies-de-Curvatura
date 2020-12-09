#pragma once

#include "ofMain.h"
#include "math.h"
#include <vector>
#include "ofxGui.h"
#include <windows.h>

class ofApp : public ofBaseApp{

	private:
		ofEasyCam cam;
		ofMesh mesh;

		ofxPanel gui;
		ofParameter <float> uiAmount;
		ofParameter <float> radiusX;
		ofParameter <float> radiusY;
		ofxIntField pointx;
		ofxIntField pointy;
		ofxToggle setzero;
		ofxButton save;
		ofxButton back;
		ofxToggle turnX;
		ofxToggle turnY;
		ofxToggle turnZ;

		bool wareframe;
		bool justpoint;
		bool campana;
		bool paraboloid;
		bool ellipsoid;
		bool hyperbolicParaboloid;
		float rotateX;
		float rotateY;
		float rotateZ;
		bool sound;

		int position;
		int width;
		int height;
		int size;
		vector<double> savedpoints;
	
	public:
		void setup();
		void update();
		void draw();
		void setsize();
		void setvector();

		int numpoint(int x, int y, int matrix);

		void keyPressed(int key);
		void keyReleased(int key);	
};
