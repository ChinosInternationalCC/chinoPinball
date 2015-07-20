#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    
	// setup OF
    //ofSetFrameRate(60);
	//ofSetVerticalSync(true);
	ofBackground( 255, 255, 255, 0);
	ofDisableArbTex();
#ifdef USE_SYPHON
    mainOutputSyphonServer.setName("Screen Output");
	//mainOutputSyphonServer.
#endif
 
#ifdef USE_MTL_MAPPING
    // ----
    _mapping = new ofxMtlMapping2D();
    _mapping->init(ofGetWidth(), ofGetHeight(), "mapping/xml/shapes.xml", "mapping/controls/mapping.xml");
#endif

	chinopinball.setup();
	
	ofEnableAlphaBlending(); //TODO TEST for send Alpha with Syphon ??
	
	bIsPhotoToMatch = false;
	bIsPhotoToMatch = setupXMLPhotoAlpha();
	
	if(bIsPhotoToMatch){
		
		scene3dinFBO.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 0);
		scene3dinFBO.begin();
		ofClear(255,255,255, 0);
		scene3dinFBO.end();
	}

}

//--------------------------------------------------------------
void testApp::update() {
    
    
    
 #ifdef USE_MTL_MAPPING
    _mapping->update();
#endif
    chinopinball.update();
	
	
	if(bIsPhotoToMatch){
		scene3dinFBO.begin();
		ofClear(255,255,255, 0);
		chinopinball.draw();
		scene3dinFBO.end();
	}
	
}

//--------------------------------------------------------------
void testApp::draw() {
    
	// Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
#ifdef USE_MTL_MAPPING
    _mapping->bind();
#endif
	
	if(bIsPhotoToMatch){
		ofSetColor(ofColor::white);
		sceneOverlapedImage.draw(0,0, ofGetWidth(), ofGetHeight());
		
		ofSetColor(255,255,255,255); // TODO set Alpha in a GUI Then easy to modify.. but may be not necessary use alpha
		scene3dinFBO.draw(0,0);
	}
	else{
		chinopinball.draw();
	}

   
	
#ifdef USE_MTL_MAPPING
    _mapping->unbind();
    
    _mapping->draw();
#endif
    
#ifdef USE_SYPHON
    mainOutputSyphonServer.publishScreen();
#endif

}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    chinopinball.keyPressed(key);
	

	if(key == OF_KEY_F1){
		ofSetLogLevel(OF_LOG_SILENT); //Play ChinoP clean of COUTS!
	}
	else if(key == OF_KEY_F2){
		ofSetLogLevel(OF_LOG_VERBOSE); //Set active all Verbose commets (OF verboses included)
	}
	else if(key == OF_KEY_F3){
		ofLog(OF_LOG_VERBOSE, "CollisionVerbose");
		ofSetLogLevel("CollisionVerbose", OF_LOG_VERBOSE); //check COUTS from Collisions
	}
	else if(key == OF_KEY_F4){
		ofLog(OF_LOG_VERBOSE, "EditorVerbose");
		ofSetLogLevel("EditorVerbose", OF_LOG_VERBOSE); //check COUTS from Editor mode.
	}
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

//--------------------------------------------------------------
bool testApp::setupXMLPhotoAlpha(){

	bool bthereisPhoto = false;
	//Get some XML extra Data
	string message = "loading extra XMl Data";
	if( XML.loadFile("projectSettings.xml") ){
		message = "projectSettings.xml loaded!";
	}else{
		message = "unable to load projectSettings.xml check folder data/projectSettings.xml";
	}
	
	cout << "projectSettings.xml loading: " << message << endl;
	
	bPhotoScenario = (bool)XML.getValue("ADD_PHOTOSCENARIO_LAYER",0, 0);
	string myPhotoScenarioPath = "";
	if(bPhotoScenario){
		myPhotoScenarioPath = XML.getValue ("PHOTOSCENARIO_LAYER"," ");
		bthereisPhoto = sceneOverlapedImage.loadImage(myPhotoScenarioPath);
		cout << "myPhotoScenarioPath " << myPhotoScenarioPath << "Is there Photo ? " << myPhotoScenarioPath << endl;
	}else{
		cout << "Raw mode game mapping (without Photo Matching) " << myPhotoScenarioPath << endl;
	}
	
	return bthereisPhoto;

}