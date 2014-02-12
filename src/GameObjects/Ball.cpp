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
void Ball::setup(ofxBulletWorldRigid &myWorld, ofVec3f pos){
    m_status = BallStatusWaiting;
    position = pos;
    world = myWorld;
    
    this->setProperties(.99, .05); // .25 (more restituition means more energy) , .95 ( friction )
    this->create(world.world, position, mass, radius);
    this->add();
    
    type = ShapeTypeBall;
    
	ofRegisterKeyEvents(this);
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

//--------------------------------------------------------------
void Ball::keyPressed(ofKeyEventArgs& e) {
    
    switch(e.key){
        case OF_KEY_RETURN:
            reset();
            break;
    }
}

//--------------------------------------------------------------
void Ball::keyReleased(ofKeyEventArgs& key) {
}

//--------------------------------------------------------------
void Ball::reset() {
    
    this->remove();
    this->create(world.world, position, mass, radius);
    this->add();
    
}
    