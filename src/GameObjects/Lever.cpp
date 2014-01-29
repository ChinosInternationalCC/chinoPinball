//
//  Lever.cpp
//  chinoPinball
//
//  Created by Kuba on 03/01/14.
//
//

#include "Lever.h"

//---------------------------------
void Lever::setup(ofxBulletWorldRigid &world, ofVec3f _pos){
    
    position = _pos;
    rotation = btQuaternion(btVector3(0,1,0), ofDegToRad(-90));
    
    // load 3D model
    ofVec3f scale(0.033, 0.033, 0.033);
	assimpModel.loadModel("Tuscan_Column.dae", true);
	assimpModel.setScale(scale.x, scale.y, scale.z);
	assimpModel.setPosition(0, 0, 0);
    
    // add 3D mashes to ofxBullet shape
    for(int i = 0; i < assimpModel.getNumMeshes(); i++)
    {
        body.addMesh(assimpModel.getMesh(i), scale, true);
    }
    //    body.addMesh(assimpModel.getMesh(0), scale, true);
    
    // create ofxBullet shape
    body.create(world.world, position, 0); // we set m=0 for kinematic body
    body.add();
    body.enableKinematic();
    
    
	// lever rotation angles
	lowerLimit = -30;
	upperLimit = 60;
    speed = 15;    // degrees per frame
    
    // distance from object center to rotation axis
    axisX = 1.3;
    
    // rotate lever to lower position
    rotate(lowerLimit);
    
    
	ofRegisterKeyEvents(this);
    isKeyPressed = false;
    
}

//--------------------------------------------------------------
void Lever::update(){
    
    if (isKeyPressed)
    {
        if (angle < upperLimit) // rotate up
        {
            angle += speed;
            rotate(angle);
        }
    }
    else
    {
        if (angle > lowerLimit) // rotate down
        {
            angle -= speed;
            rotate(angle);
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
void Lever::rotate(float degrees) {
    
    btTransform transform;
    btRigidBody* a_rb = body.getRigidBody();
    a_rb->getMotionState()->getWorldTransform( transform );
    
    // rotate
    //    btQuaternion currentRotation = transform.getRotation();
    //    btQuaternion rotate = btQuaternion(btVector3(0,0,1), ofDegToRad(degrees));
    btQuaternion rotate;
    
    //    rotation.setRotation(btVector3(0,0,1), ofDegToRad(angle));
    rotate.setEuler(ofDegToRad(0), ofDegToRad(0), ofDegToRad(degrees));
    transform.setRotation(rotate * rotation);
    
    // translate
    btVector3 origin = transform.getOrigin();
    origin.setX(position.x + axisX - axisX * cos(ofDegToRad(degrees)));
    origin.setY(position.y - axisX * sin(ofDegToRad(degrees)));
    
    transform.setOrigin(origin);
    
    a_rb->getMotionState()->setWorldTransform( transform );
    
    body.activate();
}





