//
//  Lever.cpp
//  chinoPinball
//
//  Created by Kuba on 03/01/14.
//
//

#include "Lever.h"

//---------------------------------
void Lever::setup(ofxBulletWorldRigid &world){
    
    body.create(world.world, ofVec3f(3, 4, 0), 0, 4, .5, .5); // we set m=0 for kinematic body
    body.add();
    body.enableKinematic();
    
	ofRegisterKeyEvents(this);
    isKeyPressed = false;
    
	//degrees
	lowerLimit = -30;
	upperLimit = 60;
    speed = 15;    // degrees per frame
    
    // rotate lever to lower position
    rotate(lowerLimit, 0, 0);
    
}

//--------------------------------------------------------------
void Lever::update(){
    
	// get current rotation
    ofVec3f rotation = body.getRotation();
    float rotationX = ofRadToDeg(rotation.x);
    
    if (isKeyPressed)
    {
        if (rotationX < upperLimit) // rotate up
        {
            rotate(rotationX + speed, 0, 0);
        }
    }
    else
    {
        if (rotationX > lowerLimit) // rotate down
        {
            rotate(rotationX - speed, 0, 0);
        }
    }
    
}

//--------------------------------------------------------------
void Lever::draw(){
    
	ofSetColor(0, 255, 0);
    body.draw();
    
}

//--------------------------------------------------------------
void Lever::keyPressed(ofKeyEventArgs& key) {
	
	isKeyPressed = true;
    
}

//--------------------------------------------------------------
void Lever::keyReleased(ofKeyEventArgs& key) {
	
	isKeyPressed = false;
	
}

//--------------------------------------------------------------
void Lever::rotate(float a_yaw, float a_pitch, float a_roll) {
	
    btTransform transform;
    
    btRigidBody* a_rb = body.getRigidBody();
    
    a_rb->getMotionState()->getWorldTransform( transform );
    
    //btScalar yaw, pitch, roll;
    btMatrix3x3 mat = btMatrix3x3( transform.getRotation() );
    mat.setEulerYPR(ofDegToRad(a_yaw), ofDegToRad(a_pitch), ofDegToRad(a_roll));
    
    transform.setBasis( mat );
    
    a_rb->getMotionState()->setWorldTransform( transform );
    
    body.activate();
	
}


