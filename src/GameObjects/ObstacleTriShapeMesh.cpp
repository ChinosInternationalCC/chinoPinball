//
//  ObstacleTriShapeMesh.cpp
//  chinoPinball
//
//  Created by carles on 10/05/15.
//
//

#include "ObstacleTriShapeMesh.h"


ObstacleTriShapeMesh::ObstacleTriShapeMesh(vector <SimpleMission *> * _currentMissions) :
SimpleObject(&body, _currentMissions, -1.5)
{
	collisionPoints = 0;
	    world = NULL;
	
}

//---------------------------------
void ObstacleTriShapeMesh::setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale){
	//position.z = -1.5;
    //setDefaultZ();
	
}


//--------------------------------------------------------------
void ObstacleTriShapeMesh::setupSpecific(){
	
}


//--------------------------------------------------------------
void ObstacleTriShapeMesh::autoScalingXYZ(){
	
	
}

//--------------------------------------------------------------
void ObstacleTriShapeMesh::setDefaultPostion(){

}

//--------------------------------------------------------------
void ObstacleTriShapeMesh::updateSpecific(bool bEditorMode){
	//DO Nothing
}


//--------------------------------------------------------------
void ObstacleTriShapeMesh::draw(bool bEditorMode){
	

}

//-------------------------------------------------------------
ofxBulletTriMeshShape* ObstacleTriShapeMesh::getBulletBaseShape(){
	return (ofxBulletTriMeshShape*)&body;
}

//------------------------------------------------------------
string ObstacleTriShapeMesh::getObjectName(){
	return "ObstacleTriShapeMesh";
}

//------------------------------------------------------------
void ObstacleTriShapeMesh::onCollision(){
	
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


void ObstacleTriShapeMesh::onCollisionSpecific(){
	//Do Nothing
}

//--------------------------------------------------------------
void ObstacleTriShapeMesh::setupRot(){
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
void ObstacleTriShapeMesh::setAngle2Rotate(float angle2rot, ofVec3f axis2rot) {
	
	
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


