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
    
    position = ofVec3f(2, 4, 0);

    // load 3D model
    ofVec3f scale(0.03, 0.03, 0.03);
	assimpModel.loadModel("street_lamp.dae", true);
	assimpModel.setScale(scale.x, scale.y, scale.z);
	assimpModel.setPosition(0, 0, 0);
    
    // add 3D mash to ofxBullet shape
    body.addMesh(assimpModel.getMesh(0), scale, true);
    
    // create ofxBullet shape
    body.create(world.world, position, ofQuaternion(-3., ofDegToRad(125), 4., PI), 0); // we set m=0 for kinematic body
    body.add();
    body.enableKinematic();

    
	// lever rotation angles
	lowerLimit = -30;
	upperLimit = 60;
    speed = 15;    // degrees per frame

    // distance from object center to rotation axis
    axisX = 1;

    // rotate lever to lower position
//    rotate(lowerLimit);
    
    
	ofRegisterKeyEvents(this);
    isKeyPressed = false;

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
            rotate(rotationX + speed);
        }
    }
    else
    {
        if (rotationX > lowerLimit) // rotate down
        {
            rotate(rotationX - speed);
        }
    }

}

//--------------------------------------------------------------
void Lever::draw(){
	
	ofSetColor(255, 255, 255);
	
    material.begin();
	
    body.transformGL();
    ofPoint scale = assimpModel.getScale();
    ofScale(scale.x,scale.y,scale.z);
    assimpModel.getMesh(0).drawFaces();
    body.restoreTramsformGL();
    
	material.end();
	
}

//--------------------------------------------------------------
void Lever::keyPressed(ofKeyEventArgs& key) {

	isKeyPressed = true;

}

//--------------------------------------------------------------
void Lever::keyReleased(ofKeyEventArgs& key) {

	isKeyPressed = false;

}

//- rotate around axis ---------------------------------------
void Lever::rotate(float angle) {

    btTransform transform;
    btRigidBody* a_rb = body.getRigidBody();
    a_rb->getMotionState()->getWorldTransform( transform );

    // rotate
    btQuaternion rotation = transform.getRotation();
    rotation.setRotation(btVector3(0,0,2), ofDegToRad(angle));
    transform.setRotation(rotation);

    // translate
    btVector3 origin = transform.getOrigin();
    origin.setX(position.x + axisX - axisX * cos(ofDegToRad(angle)));
    origin.setY(position.y - axisX * sin(ofDegToRad(angle)));

    transform.setOrigin(origin);

    a_rb->getMotionState()->setWorldTransform( transform );

    body.activate();
}





