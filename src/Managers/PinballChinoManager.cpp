//
//  PinballChinoManager.cpp
//  chinoPinball
//
//  Created by Kuba on 28/12/13.
//
//

#include "PinballChinoManager.h"

PinballChinoManager::PinballChinoManager():statusDisplay(20,60){
    
}

//--------------------------------------------------------------
void PinballChinoManager::setup(){

	
    // setup bullet world
	world.setup();
	world.setGravity( ofVec3f(0, 4, 7) );
	
/*
	// setup camera
	camera.setPosition(ofVec3f(0, 0, -34.5));
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
	
	world.setCamera(&camera);	
	world.setCameraPosition(ofVec3f(0, 0, -34.5));
    
    // setup scenario
    myScenario.setup(world);
*/


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
    
	world.setCameraPosition(ofVec3f(0, 0, -34.5));
	
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
    
    statusDisplay.draw();
    
}