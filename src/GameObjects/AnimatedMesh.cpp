//
//  AnimatedObject.cpp
//  chinoPinball
//
//  Created by Ovidiu on 16/4/15.
//
//

#include "AnimatedMesh.h"
string _sysPath = "Sysiphous/sysiphus_centred.dae";


//----------------------------------
AnimatedMesh::AnimatedMesh(vector <SimpleMission *> * _currentMissions) :
SimpleObject(&body, _currentMissions, -0.511)
{
    collisionPoints = 0;
    world = NULL;
}

//---------------------------------
void AnimatedMesh::setup(ofxBulletWorldRigid &world,  SimpleObjectAttrib *Attributes){
	
	//position.z = -1.5;
	// setDefaultZ();
	
	genericSetup(world, *Attributes);
	
	//save init values
	initScale = scale;
	
}

//----------------------------------
void AnimatedMesh::setupBody(SimpleObjectAttrib &Attributes){
	
	////
	
	assimpModel.loadModel(getAnimatedMeshAttr()->modelPath, true);
	assimpModel.setScale(scale.x, scale.y, scale.z);
	assimpModel.setPosition(0, 0, 0);
	
	
	//save init values
	mesh = assimpModel.getCurrentAnimatedMesh(0);
	// create ofxBullet shape
	//body.create(world.world, position, 0); // we set m=0 for kinematic body
	body.create( world->world, mesh, getPosition(), 0.f, ofVec3f(-10000, -10000, -10000), ofVec3f(10000,10000,10000) );
	body.add();
	body.enableKinematic();
	body.setActivationState( DISABLE_DEACTIVATION );
	
	
	bAnimate = true;
	assimpModel.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	assimpModel.playAllAnimations();
	body.add();
	
	
	//Set properties to the body // TODO check others if they are setted
	body.setProperties(3, .95); // restitution, friction
	body.setDamping( .25 );
	body.activate();
	
}



//----------------------------------
void AnimatedMesh::setupLookStyle(SimpleObjectAttrib &Attributes){
	//NOTHING
}

//----------------------------------
void AnimatedMesh::setupAnimations(SimpleObjectAttrib &Attributes){
	
	collisionTime = -120;
}

//----------------------------------
void AnimatedMesh::setupType(){
	type = ShapeTypeAnimatedMesh;
}


//--------------------------------------------------------------
void AnimatedMesh::updateSpecific(bool bEditorMode){
	//TODO
}

//--------------------------------------------------------------
void AnimatedMesh::draw(bool bEditorMode){
	
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
 
    mesh = assimpModel.getCurrentAnimatedMesh(0);
    body.updateMesh( this->world->world, mesh );
    body.getRigidBody()->getCollisionShape()->setLocalScaling(btVector3(scaleModel.x, scaleModel.y,  scaleModel.z));
                                                                    
    body.transformGL();
    ofScale(scaleModel.x,scaleModel.y,scaleModel.z);    

    mesh.drawWireframe();
    
    
	body.restoreTramsformGL();
    
	glPopAttrib();
	material.end();
    
}
//-------------------------------------------------------------
ofxBulletBaseShape* AnimatedMesh::getBulletBaseShape(){
    return (ofxBulletBaseShape*)&body;
}

//------------------------------------------------------------
string AnimatedMesh::getObjectName(){
    return "Obstacle";
}

//------------------------------------------------------------
void AnimatedMesh::onCollision(){
    
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
}

//--------------------------------------------------------------
void AnimatedMesh::setupRot(){
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


//--------------------------------------------------------------
void AnimatedMesh::setAngle2Rotate(float angle2rot, ofVec3f axis2rot) {
	
	
	btTransform transform;
	btRigidBody* a_rb = body.getRigidBody();
    a_rb->getMotionState()->getWorldTransform( transform );
    
    // rotate
	btQuaternion currentRotation = transform.getRotation();
	btQuaternion rotate = btQuaternion(btVector3(axis2rot.x,axis2rot.y,axis2rot.z), ofDegToRad(angle2rot));
    
	//rotation.setRotation(btVector3(0,0,1), ofDegToRad(angle2rot));
	//rotate.setEuler(ofDegToRad(0), ofDegToRad(90), ofDegToRad(0));
	transform.setRotation(rotate * currentRotation);
    
	a_rb->getMotionState()->setWorldTransform( transform );
	
	btQuaternion Rotation2Save = a_rb->getOrientation();
	//save this var for the XML
	rotation.set(Rotation2Save.x(), Rotation2Save.y(), Rotation2Save.z(), Rotation2Save.w());
	
	body.activate();
	
	
}

//-------------------------------------------------------------
void AnimatedMesh::setAnimation(bool bAnimate) {
    this->bAnimate = bAnimate;
}

//--------------------------------------------------------------
AnimatedMeshAttrib* AnimatedMesh::getAnimatedMeshAttr(){
	return (AnimatedMeshAttrib*) getSimpleAttrib();
}

