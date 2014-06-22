//
//  chinoWorld.cpp
//  chinoPinball
//
//  Created by Kuba on 17/02/14.
//
//

#include "chinoWorld.h"

//--------------------------------------------------------------
void chinoWorld::update() {
	if(!checkWorld()) return;
	// should this run on delta time? //
    world->stepSimulation(1.0f/60.0f, 6, 1./60.);
	
	if(bDispatchCollisionEvents) {
		world->performDiscreteCollisionDetection();
		checkCollisions();
	}
}

//--------------------------------------------------------------
ofVec3f chinoWorld::getWorldPos() {
    ofxBulletRaycastData data = raycastTest(ofGetMouseX(), ofGetMouseY());
    return data.pickPosWorld;
}
