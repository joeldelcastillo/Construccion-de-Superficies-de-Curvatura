#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	
	ofBackground(255);

	setsize();
	setvector();

	bool wireframe = true;
	bool justpoint = true;
	bool campana= false;
	bool paraboloid;
	bool ellipsoid;
	bool hyperbolicParaboloid;
	//---------------------------------------
	gui.setup();
	gui.add(pointx.setup("X Position", 0, 0, width));
	gui.add(pointy.setup("Y Position", 0, 0, height));
	gui.add(uiAmount.set("Amplitud", 0, -20, 20));
	gui.add(radiusX.set("RadioX", 1, 0.001, width * 2));
	gui.add(radiusY.set("RadioY", 1, 0.001, height * 2));
	gui.add(save.setup("Save your work", false));
	gui.add(setzero.setup("Turn every point to 0", false));
	
	//gui.add(back.setup("Return to your last save point", false));

	cam.setDistance(height+ width);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			mesh.addVertex(ofPoint(x-(width/2), y - (height/ 2), 0)); 
			mesh.addColor(ofFloatColor(0,0,0));
		}
	}

	
	for (int y = 0; y < height - 1; y++) {
		for (int x = 0; x < width - 1; x++) {
			mesh.addIndex(x + y * width);               // 0
			mesh.addIndex((x + 1) + y * width);           // 1
			mesh.addIndex(x + (y + 1) * width);           // 10

			mesh.addIndex((x + 1) + y * width);           // 1
			mesh.addIndex((x + 1) + (y + 1) * width);       // 11
			mesh.addIndex(x + (y + 1) * width);           // 10
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	if (justpoint) {

		position = numpoint(pointx, pointy, width);
		ofVec3f point = mesh.getVertex(position);
		point.z = uiAmount;
		mesh.setVertex(position, point);
	}

	if (campana)
	{

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				int pos = numpoint(x, y, width);
				ofVec3f point = mesh.getVertex(pos);
				point.z = savedpoints.at(pos) + uiAmount *
					exp(-(
						((x - pointx) * (x - pointx)) / radiusX
						+ ((y - pointy) * (y - pointy)) / radiusY));
				mesh.setVertex(pos, point);

			}
		}
	}

	if (paraboloid)
	{
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				int pos = numpoint(x, y, width);
				ofVec3f point = mesh.getVertex(pos);
				point.z = savedpoints.at(pos) +  -uiAmount / 100 *(((x - pointx) * radiusX/10 * (x - pointx) * radiusX/10) +
					((y - pointy) * radiusY/10 * (y - pointy) * radiusY/10) );
				mesh.setVertex(pos, point);

			}
		}
	}

	if (hyperbolicParaboloid)
	{
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				int pos = numpoint(x, y, width);
				ofVec3f point = mesh.getVertex(pos);
				point.z = savedpoints.at(pos) +  -uiAmount / 100 * (((x - pointx) * radiusX / 10 * (x - pointx) * radiusX / 10) -
					((y - pointy) * radiusY / 10 * (y - pointy) * radiusY / 10));
				mesh.setVertex(pos, point);

			}
		}
	}

	if (ellipsoid)
	{

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				
				int pos = numpoint(x, y, width);
				ofVec3f point = mesh.getVertex(pos);
				point.z = savedpoints.at(pos) +  sqrt(uiAmount  * (1- ((x - pointx) /radiusX  * (x - pointx) /radiusX ) -
					((y - pointy) / radiusY  * (y - pointy) /radiusY )));
				mesh.setVertex(pos, point);

			}
		}
	}



	if (setzero) {
		int count = 0;
		position = 0;
		uiAmount = 0;
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				ofVec3f pint = mesh.getVertex(count);
				pint.z = 0;
				mesh.setVertex(count, pint);
				count++;

			}
		}

	}


	if (save)
	{
		savedpoints.clear();
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {

				int pos = numpoint(x, y, width);
				ofVec3f point = mesh.getVertex(pos);
				savedpoints.push_back(point.z);
			}
		}
	}


	//if(back) {
	//	for (int y = 0; y < height; y++) {
	//		for (int x = 0; x < width; x++) {

	//			int pos = numpoint(x, y, width);

	//			ofVec3f point = mesh.getVertex(pos);
	//			point.z = savedpoints.at(pos);
	//			mesh.setVertex(pos, point);
	//			cout << savedpoints.at(pos) << "  ";
	//		}
	//		cout << endl;
	//	}
	//	cout << endl;
	//}

}

//--------------------------------------------------------------
void ofApp::draw() {
	
	ofPushMatrix();

	cam.begin();
	
	if (wareframe) {
		mesh.drawWireframe();
	}
	else {
		mesh.drawVertices();
	}
	
	float space = 1;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			ofDrawBitmapString(x,
				x - (width / 2),
				0 - (height / 2) - space);


			ofDrawBitmapString(y,
				0 - (width / 2) - space,
				y - (height / 2));
		}
	}

	cam.end();


	ofPopMatrix();
	gui.draw();
	


	string msg = "f: toggle full screen \n";
	string msg1 = "j: pull just a point \n";
	string msg2 = "c: campana nature to pull a point \n";
	string msg3 = "p: elliptic paraboloid nature to pull a point \n";
	string msg4 = "h: hyperbolic paraboloid nature to pull a point \n";
	string msg5 = "e: elipsoid nature to pull a point \n";
	string msg6 = "w: draw wireframe or point cloud";

	ofDrawBitmapString(msg+msg1+msg2 + msg3+ msg4 + msg5 + msg6, 20, ofGetHeight()* 6/7);
	ofSetColor(100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	switch (key) {
	case 'f':
		ofToggleFullscreen();
		break;

	case 'j':
		justpoint = true;
		campana = false;
		paraboloid = false;
		hyperbolicParaboloid = false;
		ellipsoid = false;
		break;

	case 'c':
		campana = true;
		justpoint = false;
		paraboloid = false;
		hyperbolicParaboloid = false;
		ellipsoid = false;
		break;

	case 'p':
		paraboloid = true;
		justpoint = false;
		campana = false;
		hyperbolicParaboloid = false;
		ellipsoid = false;
		break;

	case 'h':
		hyperbolicParaboloid = true;
		paraboloid = false;
		justpoint = false;
		campana = false;
		ellipsoid = false;
		break;

	case 'e':
		ellipsoid = true;
		hyperbolicParaboloid = false;
		paraboloid = false;
		justpoint = false;
		campana = false;
		break;

	case 'w':
		wareframe = !wareframe;
		break;

	/*case 'p':
		b_perlinMesh = !b_perlinMesh;
		break;*/

	/*case 's':
		savepoints();

	case 'z':
		lastpoints();*/
	}
	

	

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

int ofApp::numpoint(int x, int y, int wd) {
	return (y*wd +x);
}


void ofApp::setsize() {
	int h;
	bool stop = false;

	while (stop == false) {
		cout << "Insert matrix Width:" << endl;
		cin >> width;
		cout << "Insert matrix Height:" << endl;
		cin >> h;

		if (h >= width) {
			height = h;
			stop = true;
		}
		else {
			cout << "Be sure with < height" << endl;
			cout << endl;
		}
	}
}

void ofApp::setvector() {
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			savedpoints.push_back(0);
		}
	}
}

