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
void Ball::setup(ofxBulletWorldRigid &world){
    m_status = BallStatusWaiting;
    
    /*BulletBallShape = new ofxBulletSphere();
	BulletBallShape->create(world.world, ofVec3f(0, 0, 0), 0.1, .25);
	BulletBallShape->add();*/
    
    this->create(world.world, ofVec3f(0, 0, 0), 0.1, .25);
    this->add();
}

//----------------------------------
void Ball::update(void){
    
}

//--------------------------------------------------------------
void Ball::drawBall(void){
    
	ofSetColor(225, 225, 225);
	//BulletBallShape->draw();
    this->draw();
    
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

