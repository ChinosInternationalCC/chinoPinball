//
//  SimpleObject.cpp
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//

#include "SimpleObject.h"

SimpleObject::SimpleObject(ofxBulletBaseShape *poBulletBaseShape,
                           vector <SimpleMission *> * _currentMissions,
                           float _DefaultPositionZ){
   
    poSimpleBody = poBulletBaseShape;
	ObjectId = -1;
	bAnimation = false;
    color = 0xffffff;
	bVisible = true;
    highlightColor = 0xff00ff;

    //xlast_scale = scale;
	scaleXyz = 0; last_scaleXyz = scaleXyz;
	
    highlightTime = 60; // what units?

    bDebugMode = false;
	
	last_angleValX = angleValX = 0;
	last_angleValY = angleValY = 0;
	last_angleValZ = angleValZ = 0;
	
	axis2RotateX = ofVec3f(1,0,0);
	axis2RotateY = ofVec3f(0,1,0);
	axis2RotateZ = ofVec3f(0,0,1);

	
	//////
	this->idCurrtentMission = 0;
	this->currentMissions = _currentMissions;
	
	collisionPoints = 0;
    
    fDefaultPositionZ = _DefaultPositionZ;

	/* init pointers */
	pAttrib = NULL;
	world = NULL;

}

//--------------------------------------------------------------
void SimpleObject::genericSetup(ofxBulletWorldRigid &myWorld, SimpleObjectAttrib &Attributes){
    
    pAttrib = &Attributes;
    
	//scale = pAttrib->ModelScale;
	
	//save init values
	//initScale = scale;
	
	
	//TODO scale
	initScale = pAttrib->ModelScale;
	last_scale = initScale;
	
    setupType();
    world = &myWorld;
    setupBody(Attributes);
    
    
    setPosition(Attributes.position);
    setDefaultZ();//Only after create it
    

    setupLookStyle(Attributes);
    setupAnimations(Attributes);

}


//--------------------------------------------------------------
void SimpleObject::setCurrentMissionId(int _idCurrentMission){
	this->idCurrtentMission = _idCurrentMission;
}

//--------------------------------------------------------------
void SimpleObject::update(bool bEditorMode){
    
	autoScalingXYZ();
    
    assimpModel.update();

	
	if(getPosition().x != last_positionX){
		setPhysicsPosition(getPosition());
		last_positionX = getPosition().x;
	}
	if(getPosition().y != last_positionY){
		setPosition(getPosition());
		last_positionY = getPosition().y;
	}
	if(getPosition().z != last_positionZ){
		setPosition(getPosition());
		last_positionZ = getPosition().z;
	}
	
	
	if(angleValX != last_angleValX){
		
		setAngle2Rotate(angleValX, axis2RotateX); //, angleValY, axis2RotateY, angleValZ, axis2RotateZ);
		last_angleValX = angleValX;
	}
	if(angleValY != last_angleValY){
		
		setAngle2Rotate(angleValY, axis2RotateY); // , angleValY, axis2RotateY, angleValZ, axis2RotateZ);
		last_angleValY = angleValY;
	}
	if(angleValZ != last_angleValZ){
		
		setAngle2Rotate(angleValZ, axis2RotateZ); //, angleValY, axis2RotateY, angleValZ, axis2RotateZ);
		last_angleValZ = angleValZ;
	}
	
	//poSimpleBody->activate();
    
    updateSpecific(bEditorMode);
    
}

//--------------------------------------------------------------
//void SimpleObject::draw(bool bEditorMode){
//}

//--------------------------------------------------------------
void SimpleObject::SetObjectId(int objId){
    ObjectId = objId;
    
}
//--------------------------------------------------------------
int SimpleObject::GetObjectId(void){
    return ObjectId;
}

//--------------------------------------------------------------
void SimpleObject::setDebugMode(bool &DebugMode){
    this->bDebugMode = DebugMode;
    
}

//--------------------------------------------------------------
void SimpleObject::drawDebug(void){
    
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("ID:"+ofToString(GetObjectId()), pAttrib->position.x,pAttrib->position.y);
        ofDrawBitmapString("HIT:"+ofToString((*currentMissions)[idCurrtentMission]->isElementHit(GetObjectId())), pAttrib->position.x,pAttrib->position.y+1);
}

//--------------------------------------------------------------
void SimpleObject::setPointsCollision(int points){
	collisionPoints = points;
}

//--------------------------------------------------------------
void SimpleObject::setVisibility(int invisible){
	if(invisible == 1)
	bVisible = false;
	else bVisible = true;
}

//--------------------------------------------------------------
void SimpleObject::setDefaultZ(){
  
    if(poSimpleBody->checkCreate()){
        pAttrib->position.z = fDefaultPositionZ;
        setPhysicsPosition(pAttrib->position);
    }else {
        cout << "Error the Object must setDefaultZ after create the object in the world" << endl;
    }
    
}

//--------------------------------------------------------------
void SimpleObject::setPhysicsPosition(ofVec3f position){
    btTransform transform;
    btRigidBody* rigidBody = poSimpleBody->getRigidBody();
    rigidBody->getMotionState()->getWorldTransform( transform );
    btVector3 origin;
    origin.setX(position.x);
    origin.setY(position.y);
    origin.setZ(position.z);
    transform.setOrigin(origin);
    rigidBody->getMotionState()->setWorldTransform( transform );
    
}

//--------------------------------------------------------------
void SimpleObject::setPhysicsRotation(ofQuaternion rotation){
    btTransform transform;
    btRigidBody* rigidBody = poSimpleBody->getRigidBody();
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
void SimpleObject::setPosition(ofVec3f _position){
    pAttrib->position = _position;
}

//--------------------------------------------------------------
ofVec3f SimpleObject::getPosition(){
    return pAttrib->position;
}

//--------------------------------------------------------------
void SimpleObject::setDefaultPostion(){
	last_positionX = pAttrib->position.x;
	last_positionY = pAttrib->position.y;
	last_positionZ = pAttrib->position.z;
}


//--------------------------------------------------------------
ofVec3f SimpleObject::getScale(){
	return pAttrib->ModelScale;
}

//--------------------------------------------------------------
ofVec3f* SimpleObject::getScaleRef(){
	return &pAttrib->ModelScale;
}

//--------------------------------------------------------------
void SimpleObject::autoScalingXYZ(){
	
	btVector3 myObjectScale;
	ofVec3f myOfObjectScale;
	
	
	if (scaleXyz != last_scaleXyz) {
		float diff = scaleXyz - last_scaleXyz;
		last_scaleXyz = scaleXyz;
		
		//Get Scales
		myObjectScale = poSimpleBody->getRigidBody()->getCollisionShape()->getLocalScaling();
		myOfObjectScale = ofVec3f(myObjectScale.x(), myObjectScale.y(), myObjectScale.z());
        
		//Update sizes values
		myOfObjectScale += ofMap(diff, 0, initScale.z, 0, 0.45); //+= diff;
		pAttrib->ModelScale += ofMap(diff, 0, initScale.z, 0, 0.025);
		last_scale = pAttrib->ModelScale;
        
		myObjectScale.setX(myOfObjectScale.x);
		myObjectScale.setY(myOfObjectScale.y);
		myObjectScale.setZ(myOfObjectScale.z);
        
		//update physyc object
		poSimpleBody->getRigidBody()->getCollisionShape()->setLocalScaling(myObjectScale);
		assimpModel.setScale(pAttrib->ModelScale.x, pAttrib->ModelScale.y, pAttrib->ModelScale.z);
	}
    
}

//--------------------------------------------------------------
void SimpleObject::setAngle2Rotate(float angle2rot, ofVec3f axis2rot) {
	
	
	btTransform transform;
	btRigidBody* a_rb = poSimpleBody->getRigidBody();
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
	
	poSimpleBody->activate();
	
	
}

//--------------------------------------------------------------
SimpleObjectAttrib * SimpleObject::getSimpleAttrib(){
    return pAttrib;
}