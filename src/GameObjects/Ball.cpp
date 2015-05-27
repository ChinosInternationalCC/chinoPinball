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

//---------------------------------
void Ball::setup(ofxBulletWorldRigid &myWorld,
                 ofVec3f pos,
                 float mass,
                 float radius,
                 float restitution,
                 float friction){
    
    setPosition(pos);


    this->mass = mass;
    this->radius = radius;
    this->restitution = restitution;
    this->friction = friction;
    
    world = &myWorld;
    body.create(world->world, this->getPosition(), mass, radius);
    body.setProperties(restitution, friction); // .25 (more restituition means more energy) , .95 ( friction )
    body.add();
    
    setDefaultZ();//Only after create it
    
    //specific
    type = ShapeTypeBall;
    
    SoundManager::getInstance()->PlaySound(1);
    
    //position.z = -radius;
    shadow.set(radius, 0.1);
	shadow.setResolution(20, 1);
    
    
}

//----------------------------------
void Ball::update(bool bEditorMode){

    shadow.setPosition(body.getPosition().x, body.getPosition().y, 0.0);
	shadow.setRadius(radius+ofMap((-0.5-body.getPosition().z), 0, 1, 0, 0.2));

}

//--------------------------------------------------------------
void Ball::updateSpecific(bool bEditorMode){
	//TODO
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
    body.create(world->world, this->getPosition(), mass, radius);
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
ofVec3f Ball::getInitialPos(){
    return m_initialPos;
}