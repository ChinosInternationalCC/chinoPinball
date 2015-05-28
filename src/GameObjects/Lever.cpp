//
//  Lever.cpp
//  chinoPinball
//
//  Created by Kuba on 03/01/14.
//
//

#include "Lever.h"
Lever::Lever(vector <SimpleMission *> * _currentMissions):
SimpleObject(&body, _currentMissions, -0.5)
{
    
}

//--------------------------------------------------------------
void Lever::setup(ofxBulletWorldRigid &world,
                  SimpleObjectAttrib *Attributes/*
                  ofVec3f Pos,  string url, ofVec3f ModelScale, int setDirection = 1*/
                  ){
    //position.z = -0.5;
    
    
    genericSetup(world, *Attributes);
    
    //Two rotationLever to set the lever in the right position
    //rotationLever = btQuaternion(btVector3(0,1,0), ofDegToRad(-90));
    
    
    // load 3D model
    scale = getLeverAttr()->ModelScale;
	assimpModel.loadModel(ModelPath, true);
	assimpModel.setScale(scale.x, scale.y, scale.z);
	assimpModel.setPosition(0, 0, 0);
    
    // add 3D mashes to ofxBullet shape
    for(int i = 0; i < assimpModel.getNumMeshes(); i++)
    {
        body.addMesh(assimpModel.getMesh(i), scale, true);
    }
    
    
    isKeyPressed = false;
}

//----------------------------------
/**
 *  Supper Ovi Cast is used to simplify all Atributes methods of ChinoPinball.
 *  Use this line to copy the reference of the Atributes to your specifics methods
 *  >>> allAttrib *pBallAttr = (BallAttrib*) &Attributes;
 *
 *  @param Attributes reference to the Attribute object
 */
void Lever::setupBody(SimpleObjectAttrib &Attributes){
    
    // create ofxBullet shape
    body.create(world->world, getPosition(), 0); // we set m=0 for kinematic body
    

    body.setProperties(1., 0.); // .25 (more restituition means more energy) ,this	Lever *	0x21fdc00	0x021fdc00 .95 ( friction )
    //body.setProperties(getSimpleAttrib()->restitution, getSimpleAttrib()->friction);
    // .25 (more restituition means more energy) , .95 ( friction )
    body.add();
    
    body.enableKinematic();
}


//----------------------------------
void Lever::setupLookStyle(SimpleObjectAttrib &Attributes){
    //NOTHING
}

//----------------------------------
void Lever::setupAnimations(SimpleObjectAttrib &Attributes){
    rotationLever = btQuaternion(btVector3(0,0,1), ofDegToRad(90));
    // lever rotationLever angles
    angle = 0;
	upperLimit = 60;
	lowerLimit = -30;
    speed = 15;    // degrees per frame
    
    // distance from object center to rotationLever axis
    axisX = 1.3;
    
    // settings for counter clockwise rotationLever
    if (getLeverAttr()->direction == 0)
    {
        upperLimit = -upperLimit;
        lowerLimit = -lowerLimit;
        speed = -speed;
        axisX = -axisX;
    }
    
    // rotate lever to lower position
    rotate(lowerLimit);
}

//----------------------------------
void Lever::setupType(){
    type = ShapeTypeLever;
}

//--------------------------------------------------------------
void Lever::update(bool bEditorMode){
    
    if (isKeyPressed)
    {
        if ((getLeverAttr()->direction && (angle < upperLimit)) || (!getLeverAttr()->direction && (angle > upperLimit))) // rotate up
        {
            angle += speed;
            rotate(angle);
        }
    }
    if (!isKeyPressed)
    {
        if ((getLeverAttr()->direction && (angle > lowerLimit)) || (!getLeverAttr()->direction && (angle < lowerLimit))) // rotate down
        {
            angle -= speed;
            rotate(angle);
        }
    }
    
}

//--------------------------------------------------------------
void Lever::updateSpecific(bool bEditorMode){
	//TODO
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
    origin.setX(getPosition().x + axisX - axisX * cos(ofDegToRad(degrees)));
    origin.setY(getPosition().y - axisX * sin(ofDegToRad(degrees)));
    
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


//--------------------------------------------------------------
void Lever::setupRot(){
    
}

LeverAttrib* Lever::getLeverAttr(){
    return (LeverAttrib*) getSimpleAttrib();
}




