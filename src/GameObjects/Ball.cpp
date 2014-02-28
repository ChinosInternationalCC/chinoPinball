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
Ball::Ball(SimpleObject simpleObject){
    return Ball::Ball();
}

//---------------------------------
void Ball::setup(ofxBulletWorldRigid &myWorld, ofVec3f pos){
    m_status = BallStatusWaiting;
    position = pos;
    world = myWorld;
    
    body.setProperties(.99, .05); // .25 (more restituition means more energy) , .95 ( friction )
    body.create(world.world, position, mass, radius);
    body.add();
    
    type = ShapeTypeBall;
    
    SoundManager::getInstance()->PlaySound(1);
}

//----------------------------------
void Ball::update(void){
    
}

//--------------------------------------------------------------
void Ball::draw(void){
    
	ofSetColor(225, 225, 225);
	//BulletBallShape->draw();
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
    