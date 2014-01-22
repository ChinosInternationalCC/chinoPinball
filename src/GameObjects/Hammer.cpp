//
//  Hammer.cpp
//  chinoPinball
//
//  Created by Ovidiu on 12/01/14.
//
//

#include "Hammer.h"

//---------------------------------
void Hammer::setup(ofxBulletWorldRigid &world, ofVec3f position){
    
   /* position = ofVec3f(7, 4, 0);*/
                /*(world, position,  mass, sizeX, sizeY, sizeZ)*/
    body.create(world.world, position, 0, .5, 4, .5); // we set m=0 for kinematic body
    body.add();
    body.enableKinematic();
    
	ofRegisterKeyEvents(this);
    isKeyPressed = false;
    
	//y position
	lowerLimit = 0;
	upperLimit = 3;
    speed = 2;    // pos per frame
    
    
    // move hammer to lower position
    move(lowerLimit);
    
}

//--------------------------------------------------------------
void Hammer::update(){
    
	// get current translation
    ofVec3f translation = body.getPosition();
    float translationY = translation.y;
    
    if (isKeyPressed)
    {
        if (translationY < upperLimit)
        {
            move(translationY + speed);
        }
    }
    else
    {
        if (translationY > lowerLimit)
        {
            move(translationY - speed);
        }
    }
    
}

//--------------------------------------------------------------
void Hammer::draw(){
    
	ofSetColor(0, 255, 0);
    body.draw();
    
}

//--------------------------------------------------------------
void Hammer::keyPressed(ofKeyEventArgs& key) {
    
	isKeyPressed = true;
    
}

//--------------------------------------------------------------
void Hammer::keyReleased(ofKeyEventArgs& key) {
    
	isKeyPressed = false;
    
}


//- rotate around axis ---------------------------------------
void Hammer::move(float height) {
    
    btTransform transform;
    btRigidBody* a_rb = body.getRigidBody();
    a_rb->getMotionState()->getWorldTransform( transform );

    
    // translate
    btVector3 origin = transform.getOrigin();
    origin.setY(height);
    
    transform.setOrigin(origin);
    
    a_rb->getMotionState()->setWorldTransform( transform );
    
    body.activate();
}

