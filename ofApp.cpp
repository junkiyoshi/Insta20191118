#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetColor(255);
	ofNoFill();

	this->gon = 8;
	for (auto i = 0; i < this->gon; i++) {

		this->gap_list.push_back(0);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	for (auto& gap : this->gap_list) {

		gap = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.002), 0, 1, 0.01, 0.3);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	auto radius = 350;
	int deg_span = 360 / this->gon;
	vector<glm::vec2> vertices;
	auto first = true;
	while(true) {

		if(first){

			for (auto deg = 0; deg < 360; deg += deg_span) {

				vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
			}

			first = false;
		}
		else {

			vector<glm::vec2> tmp;
			for (auto k = 0; k < vertices.size(); k++) {

				tmp.push_back(vertices[k] + (vertices[(k + 1) % vertices.size()] - vertices[k]) * this->gap_list[k]);
			}
			vertices = tmp;
		}

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		if (glm::distance(vertices[0], vertices[1]) < 1) {
			
			break;
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}