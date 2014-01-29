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

    //do things just once
	bstartup = true;
	
    // setup bullet world
	world.setup();
	world.setGravity( ofVec3f(0, 10, 0) );
    world.enableGrabbing();
	

	// setup camera
	camera.setPosition(ofVec3f(0, 0, -34.5));
	camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
	
	world.setCamera(&camera);	
	world.setCameraPosition(ofVec3f(0, 0, -34.5));
    
    // setup scenario
    myScenario.setup(world);


}

//--------------------------------------------------------------
void PinballChinoManager::update(){
    
	//do things just once
	if(bstartup){
		//camera.setGlobalPosition(ofVec3f(0, 0, -34.5)); //don't work 
		bstartup = false;
	}
	
	world.setCameraPosition(ofVec3f(0, 0, -34.5));
	
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