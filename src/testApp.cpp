#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	// setup OF
    //ofSetFrameRate(60);
	//ofSetVerticalSync(true);
	ofBackground( 10, 10, 10);
#ifdef USE_SYPHON
    mainOutputSyphonServer.setName("Screen Output");
#endif

	chinopinball.setup();
}

//--------------------------------------------------------------
void testApp::update() {
    
    chinopinball.update();
    
}

//--------------------------------------------------------------
void testApp::draw() {
    
    chinopinball.draw();
#ifdef USE_SYPHON
    mainOutputSyphonServer.publishScreen();
#endif
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    chinopinball.keyPressed(key);
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
    chinopinball.keyReleased(key);
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}