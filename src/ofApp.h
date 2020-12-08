#pragma once

#include "ofMain.h"
#include "math.h"
#include <vector>
#include "ofxGui.h"

class ofApp : public ofBaseApp{
	
	public:
		void setup();
		void update();
		void draw();
		void setsize();
		void setvector();

		int numpoint(int x, int y, int matrix);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

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


		bool wareframe;
		bool justpoint;
		bool campana;
		bool paraboloid;
		bool ellipsoid;
		bool hyperbolicParaboloid;

		int position;
		int width;
		int height;
		int size;
		vector<double> savedpoints;





		
};
