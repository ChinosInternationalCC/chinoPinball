//
//  Lever.cpp
//  chinoPinball
//
//  Created by Kuba on 03/01/14.
//
//

#include "Lever.h"
Lever::Lever(vector <SimpleMission *> * _currentMissions):
SimpleObject(_currentMissions)
{
    
}

//--------------------------------------------------------------
void Lever::setup(ofxBulletWorldRigid &world, ofVec3f setPosition,  string url, ofVec3f ModelScale, int setDirection = 1){
    type = ShapeTypeLever;
    position = setPosition;
    direction = setDirection;
	ModelPath = url;
    //Two rotationLever to set the lever in the right position
    //rotationLever = btQuaternion(btVector3(0,1,0), ofDegToRad(-90));
    rotationLever = btQuaternion(btVector3(0,0,1), ofDegToRad(90));
    
    // lever rotationLever angles
    angle = 0;
	upperLimit = 60;
	lowerLimit = -30;
    speed = 15;    // degrees per frame
    
    // distance from object center to rotation axis
    axisX = 1.3;
    
    // settings for counter clockwise rotation
    if (direction == 0)
    {
        upperLimit = -upperLimit;
        lowerLimit = -lowerLimit;
        speed = -speed;
        axisX = -axisX;
        rotationLever = btQuaternion(btVector3(0,0,1), ofDegToRad(-90));
    }
    
    // create ofxBullet shape
    body.create(world.world, position, 0); // we set m=0 for kinematic body
    
    // load 3D model
    scale = ModelScale;
	assimpModel.loadModel(ModelPath, true);
	assimpModel.setScale(scale.x, scale.y, scale.z);
	assimpModel.setPosition(0, 0, 0);
    
    // add 3D mashes to ofxBullet shape
    for(int i = 0; i < assimpModel.getNumMeshes(); i++)
    {
        body.addMesh(assimpModel.getMesh(i), scale, true);
    }
    
    
    body.add();
    body.enableKinematic();
    body.setProperties(1., 0.); // .25 (more restituition means more energy) ,this	Lever *	0x21fdc00	0x021fdc00 .95 ( friction )
    
	// lever rotationLever angles
    angle = 0;
	upperLimit = 60;
	lowerLimit = -30;
    speed = 15;    // degrees per frame
    
    // distance from object center to rotationLever axis
    axisX = 1.3;
    
    // settings for counter clockwise rotationLever
    if (direction == 0)
    {
        upperLimit = -upperLimit;
        lowerLimit = -lowerLimit;
        speed = -speed;
        axisX = -axisX;
    }
    
    // rotate lever to lower position
    rotate(lowerLimit);
    
    isKeyPressed = false;
    
}

//--------------------------------------------------------------
void Lever::update(bool bEditorMode){
    
    if (isKeyPressed)
    {
        if ((direction && (angle < upperLimit)) || (!direction && (angle > upperLimit))) // rotate up
        {
            angle += speed;
            rotate(angle);
        }
    }
    if (!isKeyPressed)
    {
        if ((direction && (angle > lowerLimit)) || (!direction && (angle < lowerLimit))) // rotate down
        {
            angle -= speed;
            rotate(angle);
        }
    }
    
}

//--------------------------------------------------------------
void Lever::draw(bool bEditorMode){
	
	ofSetHexColor(color);
	
    material.begin();
	
    body.transformGL();
    ofPoint scale = assimpModel.getScale();
    ofScale(scale.x,scale.y,scale.z);
    assimpModel.getMesh(0).drawFaces();
    body.restoreTramsformGL();
    
	material.end();
    
    //    stringstream ss;
    //	ss << "move lever with spacebar" << endl;
    //	ofDrawBitmapString(ss.str().c_str(), -14.8, 3);
	
}

//--------------------------------------------------------------
void Lever::onMoveEvent() {
    
	isKeyPressed = true;
    
}

//--------------------------------------------------------------
void Lever::onReleaseEvent() {
    
	isKeyPressed = false;
    
}




//- rotate around axis ---------------------------------------
void Lever::rotate(float degrees) {
    
    btTransform transform;
    btRigidBody* a_rb = body.getRigidBody();
    a_rb->getMotionState()->getWorldTransform( transform );
    
    // rotate
    //    btQuaternion currentrotationLever = transform.getrotation();
    //    btQuaternion rotate = btQuaternion(btVector3(0,0,1), ofDegToRad(degrees));
    btQuaternion rotate;
    
    //    rotation.setRotation(btVector3(0,0,1), ofDegToRad(angle));
    rotate.setEuler(ofDegToRad(0), ofDegToRad(0), ofDegToRad(degrees));
    transform.setRotation(rotate * rotationLever);
    
    // translate
    btVector3 origin = transform.getOrigin();
    origin.setX(position.x + axisX - axisX * cos(ofDegToRad(degrees)));
    origin.setY(position.y - axisX * sin(ofDegToRad(degrees)));
    
    transform.setOrigin(origin);
    
    a_rb->getMotionState()->setWorldTransform( transform );
    
    body.activate(); // Necesary to update the physic world model with the updated rotation
}

//-------------------------------------------------------------
ofxBulletBaseShape* Lever::getBulletBaseShape(){
    return (ofxBulletBaseShape*)&body;
}

//------------------------------------------------------------
string Lever::getObjectName(){
    return "Lever";
}

//------------------------------------------------------------
void Lever::onCollision(){}


//------------------------------------------------------------
void Lever::setDefaultZ(){
    
    position.z = -0.5;
    setPosition(position);
    
}

//------------------------------------------------------------
void Lever::setPosition(ofVec3f position){
    
    btTransform transform;
    btRigidBody* rigidBody = body.getRigidBody();
    rigidBody->getMotionState()->getWorldTransform( transform );
    btVector3 origin;
    origin.setX(position.x);
    origin.setY(position.y);
    origin.setZ(position.z);
    transform.setOrigin(origin);
    rigidBody->getMotionState()->setWorldTransform( transform );
    
}


//------------------------------------------------------------
void Lever::setRotation(ofQuaternion rotation){
}

//--------------------------------------------------------------
void Lever::setupRot(){
    
}






