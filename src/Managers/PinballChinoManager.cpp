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
    
    // setup OF
    ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground( 10, 10, 10);
    
    // setup bullet world
	world.setup();
	world.setGravity( ofVec3f(0, 3, 6) );
    world.enableGrabbing();
	
    // setup camera
	camera.setPosition(ofVec3f(0, 0, -15.f));
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
    camera.setDistance(20);
	world.setCamera(&camera);
    
    // setup scenario
    myScenario.setup(world);
    
}

//--------------------------------------------------------------
void PinballChinoManager::update(){
    
	world.update();
    myScenario.update();
    
}

//--------------------------------------------------------------
void PinballChinoManager::draw(){
    
	glEnable( GL_DEPTH_TEST );
	camera.begin();
    
//	ofEnableLighting();
//	light.enable();
    
    
    // debug draw
	world.drawDebug();
	
    myScenario.draw();
    
	
//	light.disable();
//	ofDisableLighting();
    
	camera.end();
    glDisable(GL_DEPTH_TEST);
    
}