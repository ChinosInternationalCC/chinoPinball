//
//  Hammer.cpp
//  chinoPinball
//
//  Created by Ovidiu on 12/01/14.
//
//

#include "Hammer.h"

Hammer::Hammer(vector <SimpleMission *> * _currentMissions) :
    SimpleObject(_currentMissions)
{
    
}

//---------------------------------
void Hammer::setup(ofxBulletWorldRigid &world, ofVec3f pos){
    
   /* position = ofVec3f(7, 4, 0);*/
                /*(world, position,  mass, sizeX, sizeY, sizeZ)*/
    position = pos;
    body.create(world.world, position, 0, .75, 4, .75); // we set m=0 for kinematic body
    body.add();
    body.enableKinematic();
    body.setProperties(1., 0.); // .25 (more restituition means more energy) , .95 ( friction )
    
    isKeyPressed = false;
    
	//y position
	lowerLimit = position.y;
	upperLimit = position.y+2;
    speed = 0.8;    // pos per frame
    
    color = 0x00ff00;
    
    
    // move hammer to lower position
    move(lowerLimit);
    
    type = ShapeTypeHammer;
    
}

//--------------------------------------------------------------
void Hammer::update(bool bEditorMode){
    
    lowerLimit = position.y;
	upperLimit = position.y+2;
    
	// get current translation
    ofVec3f translation = body.getPosition();
    float translationY = translation.y;
    
    if (isKeyPressed)
    {
        if (translationY < upperLimit)
        {
            move(translationY + speed/8);
        }
		
		bLaunch = false;
    }
    else
    {
		if(!bEditorMode){
			if (translationY > lowerLimit)
			{

				move(translationY - speed);
			}
			else{
				//TODO play once the sound play
				if(!bLaunch){
					bLaunch = true;
					//Launch Event
					eventGame lanchHammerSoundEvent;
					lanchHammerSoundEvent.gameEvent = eventGame::GAME_EVENT_HAMMER_LAUNCH;
					ofNotifyEvent(eventGame::onGameEvent, lanchHammerSoundEvent);
					//ofNotifyEvent(eventComunication::onNewCom, newComEvent);					
				}
			}
		}
    }
	
	//Update Physic work rotation if GUI change it
	if(rotation != last_rotation){
		setRotation(rotation);
		last_rotation = rotation;
	}

    
}

//--------------------------------------------------------------
void Hammer::draw(bool bEditorMode){
    
	int t = ofGetElapsedTimef()*100-collisionTime;
    if(t<highlightTime){
        ofSetHexColor(highlightColor);
    }else{
        ofSetHexColor(color);
    }
    
	material.begin();
    body.draw();
    material.end();
}



//--------------------------------------------------------------
void Hammer::onMoveEvent() {
    
	isKeyPressed = true;
    
}

//--------------------------------------------------------------
void Hammer::onReleaseEvent() {
    
	isKeyPressed = false;
    
}


//- rotate around axis ---------------------------------------
void Hammer::move(float height) {
    
    btTransform transform;
    btRigidBody* a_rb = body.getRigidBody();
    a_rb->getMotionState()->getWorldTransform( transform );

    
    // translate
    btVector3 origin = transform.getOrigin();
    origin.setY(height);
    
    transform.setOrigin(origin);
    
    a_rb->getMotionState()->setWorldTransform( transform );
    
    body.activate();
}

//------------------------------------------------------------
ofxBulletBaseShape* Hammer::getBulletBaseShape(){
    return (ofxBulletBaseShape*)&body;
}

//------------------------------------------------------------
string Hammer::getObjectName(){
    return "Hammer";
}

//------------------------------------------------------------
void Hammer::onCollision(){

    //save time to show color during some time
    collisionTime = ofGetElapsedTimef()*100;

}

//------------------------------------------------------------
void Hammer::setDefaultZ(){
    
    position.z = -0.375;
    setPosition(position);
    
}

//------------------------------------------------------------
void Hammer::setPosition(ofVec3f position){

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
void Hammer::setRotation(ofQuaternion rotation){
    
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

//--------------------------------------------------------------
void Hammer::setupRot(){
	btTransform transform;
	btRigidBody* a_rb = body.getRigidBody();
	a_rb->getMotionState()->getWorldTransform( transform );
	
	btQuaternion currentRotation = transform.getRotation();
	//rotation.set(0, 0, 0, 0);
	rotation.set(currentRotation.x(), currentRotation.y(), currentRotation.z(), currentRotation.w());
    last_rotation = rotation;
	
	transform.setRotation(currentRotation);
	a_rb->getMotionState()->setWorldTransform( transform );
}


