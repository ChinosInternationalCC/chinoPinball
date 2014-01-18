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
    
    ofSetFrameRate(120);
	ofSetVerticalSync(true);
	ofBackground( 10, 10, 10);
    
	world.setup();
	world.setGravity( ofVec3f(0, 10, 0) );
    world.enableGrabbing();
	
    // setup camera
	camera.setPosition(ofVec3f(0, 0, -10.f));
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
	world.setCamera(&camera);
    
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
    
	ofEnableLighting();
	light.enable();
    
    
    // debug draw
	world.drawDebug();
	
    myScenario.draw();
    
	
	light.disable();
	ofDisableLighting();
    
	camera.end();
    glDisable(GL_DEPTH_TEST);
}