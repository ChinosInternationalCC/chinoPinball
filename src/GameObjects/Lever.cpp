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

    position = ofVec3f(3, 4, 0);

    body.create(world.world, position, 0, 4, .5, .5); // we set m=0 for kinematic body
    body.add();
    body.enableKinematic();

	ofRegisterKeyEvents(this);
    isKeyPressed = false;

	//degrees
	lowerLimit = -30;
	upperLimit = 60;
    speed = 15;    // degrees per frame

    // position of rotation axis, relative to body center
    axisX = 1.5;

    // rotate lever to lower position
    rotate(lowerLimit);

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





