//
//  SimpleObject.cpp
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//

#include "SimpleObject.h"

//--------------------------------------------------------------
void SimpleObject::setup(ofxBulletWorldRigid &world){
    
    shape = new ofxBulletSphere();
	shape->create(world.world, ofVec3f(0, 0, 0), 0.1, .25);
	shape->add();
    
}

//--------------------------------------------------------------
void SimpleObject::update(){
}

//--------------------------------------------------------------
void SimpleObject::draw(){
    
	ofSetColor(225, 225, 225);
	shape->draw();
    
}