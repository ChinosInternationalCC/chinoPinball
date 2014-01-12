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
}

//---------------------------------
void Ball::setup(ofxBulletWorldRigid &world, ofVec3f position){
    m_status = BallStatusWaiting;
    
    this->create(world.world, position, 0.1, .25);
    this->add();
}

//----------------------------------
void Ball::update(void){
    
}

//--------------------------------------------------------------
void Ball::draw(void){
    
	ofSetColor(225, 225, 225);
	//BulletBallShape->draw();
    ofxBulletSphere::draw();
    
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

