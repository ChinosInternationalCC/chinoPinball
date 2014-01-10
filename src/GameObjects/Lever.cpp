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
    
    body.create(world.world, ofVec3f(3, 4, 0), 0.05, 4, .5, .5); // we set m=0 for a kinematic object
    body.add();
    
	//degrees
	float lowerLimit = 5;
	float upperLimit = 70;
	
    joint.create( world.world, &body, ofVec3f(4.5, 4, 0));
    joint.setAngularLowerLimit(0, 0, ofDegToRad(lowerLimit));
    joint.setAngularUpperLimit(0, 0, ofDegToRad(upperLimit));
    joint.add();
	
	
	vecRot = ofVec3f(0,0,0);
	
	
	ofRegisterKeyEvents(this);

}

//--------------------------------------------------------------
void Lever::update(){
	

}

//--------------------------------------------------------------
void Lever::draw(){
    
	ofSetColor(0, 255, 0);
    body.draw();
	
	//joint.draw();
	joint.drawJointConstraints();	
}

//--------------------------------------------------------------
void Lever::applyPushLeft(){

	counter = 100;
	
	//vecRot.x = counter;
	//vecRot.y = counter;
	vecRot.z = counter;
	
	body.applyTorque(vecRot);
	
	cout << "applyPushLeft()" << endl;
}

//--------------------------------------------------------------
void Lever::keyPressed(ofKeyEventArgs& key) {
	
	applyPushLeft();
}

//--------------------------------------------------------------
void Lever::keyReleased(ofKeyEventArgs& key) {
	
}

//--------------------------------------------------------------
void Lever::rotateLever(float a_yaw, float a_pitch, float a_roll){
	
	btTransform transform;
	
	btRigidBody* a_rb = body.getRigidBody();
	
	a_rb->getMotionState()->getWorldTransform( transform );
	
}


