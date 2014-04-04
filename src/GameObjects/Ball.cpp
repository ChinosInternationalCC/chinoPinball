//
//  Ball.cpp
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 29/12/13.
//
//

#include "Ball.h"

//---------------------------------
Ball::Ball(void){
    m_status = BallStatusWaiting;
	radius = .3;
	mass = 2;
}

//---------------------------------
void Ball::setup(ofxBulletWorldRigid &myWorld, ofVec3f pos){
    m_status = BallStatusWaiting;
    position = pos;
    
    // place on table
//    position.z = -radius/2.;
    
    world = myWorld;
    body.create(world.world, position, mass, radius);
    body.setProperties(1., 0.); // .25 (more restituition means more energy) , .95 ( friction )
    body.add();
    
    type = ShapeTypeBall;
    
    SoundManager::getInstance()->PlaySound(1);
}

//----------------------------------
void Ball::update(void){
    
}

//--------------------------------------------------------------
void Ball::draw(void){
    
	ofSetHexColor(color);
    body.draw();
    
}

//---------------------------------
bool Ball::setGameOverBall(void){
    if (m_status == BallStatusGameOver)
        return false;
    m_status = BallStatusGameOver;
    return true;
}

//--------------------------------
bool Ball::isInsideScenario(ofBoxPrimitive box){
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
void Ball::setPosition(ofVec3f position){
    
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

    