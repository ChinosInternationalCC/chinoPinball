//
//  Ball.cpp
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 29/12/13.
//
//

#include "Ball.h"

//---------------------------------
Ball::Ball(vector <SimpleMission *> * _currentMissions,  float radius) : SimpleObject(&body, _currentMissions, -radius)
{
    
}

Ball::~Ball(){
    //remove the ball from the physics
    body.remove();
    
}
//---------------------------------
void Ball::setup(ofxBulletWorldRigid &myWorld,
                 SimpleObjectAttrib *Attrib/*
                 ofVec3f pos,
                 float mass,
                 float radius,
                 float restitution,
                 float friction*/){
                     
    genericSetup(myWorld, *Attrib);
    
    //specific
    SoundManager::getInstance()->PlaySound(1);
    shadow.set(getBallAttr()->radius, 0.1);
	shadow.setResolution(20, 1);
	m_enBallState = BALL_STATE_INIT;
    
}
//----------------------------------
/**
 *  Supper Ovi Cast is used to simplify all Atributes methods of ChinoPinball.
 *  Use this line to copy the reference of the Atributes to your specifics methods
 *  >>> allAttrib *pBallAttr = (BallAttrib*) &Attributes;
 *
 *  @param Attributes reference to the Attribute object
 */
void Ball::setupBody(SimpleObjectAttrib &Attributes){
    
    body.create(world->world, this->getPosition(), getBallAttr()->mass, getBallAttr()->radius);
    body.setProperties(getBallAttr()->restitution, getBallAttr()->friction);
    // .25 (more restituition means more energy) , .95 ( friction )
    body.add();
	//body.setData(this);
    
   
}


//----------------------------------
void Ball::setupLookStyle(SimpleObjectAttrib &Attributes){
//NOTHING
}

//----------------------------------
void Ball::setupAnimations(SimpleObjectAttrib &Attributes){
//NOTHING
}

//----------------------------------
void Ball::setupType(){
    type = ShapeTypeBall;
}

//--------------------------------------------------------------
void Ball::updateSpecific(bool bEditorMode){
	//TODO
	shadow.setPosition(body.getPosition().x, body.getPosition().y, 0.0);
	shadow.setRadius(getBallAttr()->radius+ofMap((-0.5-body.getPosition().z), 0, 1, 0, 0.2));
}

//--------------------------------------------------------------
void Ball::draw(bool bEditorMode){
    
	ofSetHexColor(color);
	
	material.begin();
    body.draw();
    material.end();
	
    if(bEditorMode && bSelectedInEditor){
        ofSetHexColor(highlightColor);
    }
    else{
        ofSetColor(ofColor::black);
    }
	
	//black color
	ofPushMatrix();
		ofTranslate(shadow.getPosition());
		ofRotate(90, 1, 0, 0);
		ofTranslate(-shadow.getPosition());
		shadow.draw();
	ofPopMatrix();
    
}

//--------------------------------
bool Ball::isInsideBox(ofVec3f boxSize){
    
    btTransform transform;
    btRigidBody* rigidBody = body.getRigidBody();
    rigidBody->getMotionState()->getWorldTransform( transform );
    btVector3 origin;
    origin = transform.getOrigin();
    
    if ((origin.getX() > boxSize.x) ||
        (origin.getY() > boxSize.y) ||
        (origin.getZ() > boxSize.z))
        return false;
    else
        return true;
}

//--------------------------------------------------------------
void Ball::reset() {
    
    body.remove();
    body.create(world->world, this->getPosition(), getBallAttr()->mass, getBallAttr()->radius);
    body.add();
	//body.setData(this);
    SoundManager::getInstance()->PlaySound(1);
	m_enBallState = BALL_STATE_INIT;
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
void Ball::onCollision(SimpleObject* Obj){}


//------------------------------------------------------------
ofVec3f Ball::getInitialPos(){
    return m_initialPos;
}

//------------------------------------------------------------
BallAttrib* Ball::getBallAttr(){
    return (BallAttrib*) getSimpleAttrib();
}

//------------------------------------------------------------
void Ball::stop(bool bStopBall){
	if(bStopBall){
		cout<<"Stop Ball"<<endl;
		body.getRigidBody()->setActivationState(ISLAND_SLEEPING);
	}
	else{
		cout<<"Resume Ball"<<endl;
		body.getRigidBody()->setActivationState(ACTIVE_TAG);
	}
}
//------------------------------------------------------------
Ball::BallState Ball::GetBallState(){
	return m_enBallState;
}
//------------------------------------------------------------
void Ball::SetBallState(BallState enState){
	m_enBallState = enState;
}