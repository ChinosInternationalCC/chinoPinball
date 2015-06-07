//
//  Obstacle.cpp
//  chinoPinball
//
//  Created by Angel on 02/02/14.
//
//

#include "Obstacle.h"



Obstacle::Obstacle(vector <SimpleMission *> * _currentMissions) :
    SimpleObject(&body, _currentMissions, -1.0)
{
    collisionPoints = 0;
}

//---------------------------------
void Obstacle::setup(ofxBulletWorldRigid &world,
                     SimpleObjectAttrib *Attributes){
    //position.z = -1.5;
   // setDefaultZ();
    
	
    genericSetup(world, *Attributes);


	
    setupSpecific();
}

/**
 *  Supper Ovi Cast is used to simplify all Atributes methods of ChinoPinball.
 *  Use this line to copy the reference of the Atributes to your specifics methods
 *  >>> allAttrib *pBallAttr = (BallAttrib*) &Attributes; 
 *  >>> getObstacleAttr() simplifies this cast
 *
 *  @param Attributes reference to the Attribute object
 */

void Obstacle::setupBody(SimpleObjectAttrib &Attributes){
	
	// create ofxBullet shape
	body.create(world->world, getPosition(), 0); // we set m=0 for kinematic body
	
    // load 3D model
	assimpModel.loadModel(getSimpleAttrib()->modelPath, true);
	assimpModel.setScale(getScale().x, getScale().y, getScale().z);
	assimpModel.setPosition(0, 0, 0);
    
    
    // add 3D meshes to ofxBullet shape
    for(int i = 0; i < assimpModel.getNumMeshes(); i++)
    {
        body.addMesh(assimpModel.getMesh(i), getScale(), true);
    }
    
    assimpModel.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    assimpModel.playAllAnimations();
    body.add();
    
	
    body.enableKinematic();
    //body.setProperties(1., 0.); // .25 (more restituition means more energy) , .95 ( friction )
    // to add force to the ball on collision set restitution to > 1
	
	body.setProperties(3, .95); // restitution, friction
	body.setDamping( .25 );
    
    
    body.activate();
}


//----------------------------------
void Obstacle::setupLookStyle(SimpleObjectAttrib &Attributes){
    //NOTHING
}

//----------------------------------
void Obstacle::setupAnimations(SimpleObjectAttrib &Attributes){
    
    collisionTime = -120;
}

//----------------------------------
void Obstacle::setupType(){
    type = ShapeTypeObstacle;
}


//--------------------------------------------------------------
void Obstacle::setupSpecific(){
    //DO Nothing
}

//--------------------------------------------------------------
void Obstacle::updateSpecific(bool bEditorMode){
    //DO Nothing
}


//--------------------------------------------------------------
void Obstacle::draw(bool bEditorMode){
	
	//>>??
	int t = ofGetElapsedTimef()*100-collisionTime;
    if(t<highlightTime){
        ofSetHexColor(highlightColor);
    }else{
        if(/*(SimpleMission::MISSION_CALIFICATIONS  == currentMission->GetMissionState()) && */
		   (*currentMissions)[idCurrtentMission]->isElementHit(GetObjectId())){
            ofSetHexColor(highlightColor);
        }
        else{
        ofSetHexColor(color);
        }
    }
	//<<??

	material.begin();

	ofPoint scaleModel		= assimpModel.getScale();
	
	 body.transformGL();
    ofScale(scaleModel.x,scaleModel.y,scaleModel.z);
    assimpModel.getMesh(0).drawFaces();
	body.restoreTramsformGL();
	
	glPopAttrib();
	material.end();

}
//-------------------------------------------------------------
ofxBulletBaseShape* Obstacle::getBulletBaseShape(){
    return (ofxBulletBaseShape*)&body;
}

//------------------------------------------------------------
string Obstacle::getObjectName(){
    return "Obstacle";
}

//------------------------------------------------------------
void Obstacle::onCollision(){
    
	GameStatus::getInstance()->AddPoints(collisionPoints);
    //save time to show color during some time
    collisionTime = ofGetElapsedTimef()*100;
    //play sound
    //SoundManager::getInstance()->PlaySound(0); // PLAYED in SoundManager
   
	//Play rele //TODO After try to move this to SimpleObject ... then all objects will
	eventComunication newComEvent;
	newComEvent.collision = true;
    newComEvent.pObject = this;
	ofNotifyEvent(eventComunication::onNewCom, newComEvent);
    
    onCollisionSpecific();
}

//--------------------------------------------------------------
void Obstacle::onCollisionSpecific(){
    //Do Nothing
}

//--------------------------------------------------------------
void Obstacle::setupRot(){
	btTransform transform;
	btRigidBody* a_rb = body.getRigidBody();
	a_rb->getMotionState()->getWorldTransform( transform );
	
	btQuaternion currentRotation = transform.getRotation();
	//rotation.set(0, 0, 0, 0);
	rotation.set(currentRotation.x(), currentRotation.y(), currentRotation.z(), currentRotation.w());
    getFreeTransform()->SetLastRotation(rotation);
	
	transform.setRotation(currentRotation);
	a_rb->getMotionState()->setWorldTransform( transform );
}

//--------------------------------------------------------------
ObstacleAttrib* Obstacle::getObstacleAttr(){
    return (ObstacleAttrib*) getSimpleAttrib();
}







