//
//  Ball.cpp
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 29/12/13.
//
//

#include "Ball.h"

//---------------------------------
Ball::Ball(vector <SimpleMission *> * _currentMissions) :
    SimpleObject(_currentMissions)
{
    m_status = BallStatusWaiting;
	radius = .5;
	mass = 1;
	
	shadow.set(radius, 0.1);
	shadow.setResolution(20, 1);
}

//---------------------------------
void Ball::setup(ofxBulletWorldRigid &myWorld, ofVec3f pos){
    m_status = BallStatusWaiting;
    position = pos;
    
    // place on table
//    position.z = -radius/2.;
    
    world = myWorld;
    body.create(world.world, position, mass, radius);
    body.setProperties(0.45, 0.25); // .25 (more restituition means more energy) , .95 ( friction )
    body.add();
    
    type = ShapeTypeBall;
    
    SoundManager::getInstance()->PlaySound(1);
}

//----------------------------------
void Ball::update(bool bEditorMode){

    shadow.setPosition(body.getPosition().x, body.getPosition().y, 0.0);
	shadow.setRadius(radius+ofMap((-0.5-body.getPosition().z), 0, 1, 0, 0.2));

}

//--------------------------------------------------------------
void Ball::draw(bool bEditorMode){
    
	ofSetHexColor(color);
	
	material.begin();
    body.draw();
    material.end();
	
	ofSetColor(ofColor::black);
	
	//black color
	ofPushMatrix();
		ofTranslate(shadow.getPosition());
		ofRotate(90, 1, 0, 0);
		ofTranslate(-shadow.getPosition());
		shadow.draw();
	ofPopMatrix();
    
}

//---------------------------------
bool Ball::setGameOverBall(void){
    if (m_status == BallStatusGameOver)
        return false;
    m_status = BallStatusGameOver;
    return true;
}

//--------------------------------
bool Ball::isInsideBox(float boxSize){
    
    btTransform transform;
    btRigidBody* rigidBody = body.getRigidBody();
    rigidBody->getMotionState()->getWorldTransform( transform );
    btVector3 origin;
    origin = transform.getOrigin();
    
    if ((origin.getX() > boxSize) ||
        (origin.getY() > boxSize) ||
        (origin.getZ() > boxSize))
        return false;
    else
        return true;
}

//--------------------------------------------------------------
void Ball::reset() {
    
    body.remove();
    body.create(world.world, position, mass, radius);
    body.add();
    SoundManager::getInstance()->PlaySound(1);
}

//------------------------------------------------------------
ofxBulletBaseShape* Ball::getBulletBaseShape(){
    return (ofxBulletBaseShape*)&body;
}

//------------------------------------------------------------
string Ball::getObjectName(){
    return "Ball";
}

//------------------------------------------------------------
void Ball::onCollision(){}


//------------------------------------------------------------
void Ball::setDefaultZ(){
    
    position.z = -radius;
    setPosition(position);
    
}

//------------------------------------------------------------
void Ball::setPosition(ofVec3f pos){
    
    position = pos;
    
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
void Ball::setRotation(ofQuaternion rotation){
    
    btTransform transform;
    btRigidBody* rigidBody = body.getRigidBody();
    rigidBody->getMotionState()->getWorldTransform( transform );
	
	btQuaternion originRot;
    originRot.setX(rotation.x());
    originRot.setY(rotation.y());
    originRot.setZ(rotation.z());
	originRot.setW(rotation.w());
    
	transform.setRotation(originRot);
	
    rigidBody->getMotionState()->setWorldTransform( transform );
    
}