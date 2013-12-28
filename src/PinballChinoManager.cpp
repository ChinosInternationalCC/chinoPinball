//
//  PinballChinoManager.cpp
//  chinoPinball
//
//  Created by Kuba on 28/12/13.
//
//

#include "PinballChinoManager.h"

//--------------------------------------------------------------
void PinballChinoManager::setup(){
    
    ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground( 10, 10, 10);
	
	camera.setPosition(ofVec3f(0, 0, -10.f));
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
    
	world.setup();
	world.enableGrabbing();
	//world.enableDebugDraw();
	world.setCamera(&camera);
    
}

//--------------------------------------------------------------
void PinballChinoManager::update(){
}

//--------------------------------------------------------------
void PinballChinoManager::draw(){
}