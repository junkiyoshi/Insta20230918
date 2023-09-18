#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
	ofSetLineWidth(2);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 50, true, true, true);
	//this->word = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	this->word = "0123456789";

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 50 < 25) {

		this->noise_param += ofMap(ofGetFrameNum() % 50, 0, 25, 0.3, 0.001);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofColor color;
	ofSeedRandom(39);
	for (int i = 0; i < 400; i++) { 

		ofPushMatrix();
		ofRotateZ(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, 0, 360));
		ofRotateY(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, 0, 360));
		ofRotateX(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, 0, 360));

		auto z = ofRandom(270, 280);
		auto base_location = glm::vec3(-25, 25, z);

		ofPath chara_path = this->font.getCharacterAsPoints(this->word[(int)ofMap(ofNoise(ofRandom(1000), this->noise_param), 0, 1, 0, this->word.size())], true, false);
		vector<ofPolyline> outline = chara_path.getOutline();

		ofFill();
		ofSetColor(0);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);
			
			auto vertices = outline[outline_index].getResampledByCount(100).getVertices();
			for (auto& vertex : vertices) {

				ofVertex(vertex + base_location);
			}
		}
		ofEndShape(true);

		ofNoFill();
		ofSetColor(255);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			ofNextContour(true);

			auto vertices = outline[outline_index].getResampledByCount(100).getVertices();
			for (auto& vertex : vertices) {

				ofVertex(vertex + base_location);
			}
		}
		ofEndShape(true);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}