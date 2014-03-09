//
//  SimpleObject.cpp
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//

#include "SimpleObject.h"

SimpleObject::SimpleObject(){
	idobject = -1;
	bAnimation = false;
    color = 0xffffff;
    highlightColor = 0xff00ff;
    highlightTime = 60; // what units?
}

//--------------------------------------------------------------
void SimpleObject::setup(ofxBulletWorldRigid &world, ofVec3f _pos){
}

//--------------------------------------------------------------
//void SimpleObject::update(){
//}

//--------------------------------------------------------------
//void SimpleObject::draw(){
//}



