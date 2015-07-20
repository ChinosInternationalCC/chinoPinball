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
                           float _DefaultPositionZ)
:oFreeTransform(this){
   
    poSimpleBody = poBulletBaseShape;
	ObjectId = -1;
	bAnimation = false;
    color = 0xffffff;
	bVisible = true;
    highlightColor = 0xff00ff;
    bSelectedInEditor = false;

	
    highlightTime = 60; // what units?

    bDebugMode = false;

	
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
void SimpleObject::modifyDefaultZ(float _DeltaZ){
	
	fDefaultPositionZ += _DeltaZ;
	
}

//--------------------------------------------------------------
void SimpleObject::genericSetup(ofxBulletWorldRigid &myWorld, SimpleObjectAttrib &Attributes){
    
    pAttrib = &Attributes;
    
	//scale = pAttrib->ModelScale;
	
	//save init values
	//initScale = scale;
	
	
	//TODO scale
	initScale = pAttrib->ModelScale;
	getFreeTransform()->SetLastScale(initScale);
	
    setupType();
    world = &myWorld;
    setupBody(Attributes);
    
    
    setPosition(Attributes.position);
	
	if(type != ShapeTypeScenario){
		//setDefaultZ();//Only after create it
	}

    setupLookStyle(Attributes);
    setupAnimations(Attributes);
}


//--------------------------------------------------------------
void SimpleObject::setCurrentMissionId(int _idCurrentMission){
	this->idCurrtentMission = _idCurrentMission;
}

//--------------------------------------------------------------
void SimpleObject::update(bool bEditorMode){
    
	getFreeTransform()->autoScalingXYZ();
    
    assimpModel.update();
    
    oFreeTransform.update();
    
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

    /*
	last_positionX = pAttrib->position.x;
	last_positionY = pAttrib->position.y;
	last_positionZ = pAttrib->position.z;
     */
}


//--------------------------------------------------------------
ofVec3f SimpleObject::getScale(){
	return pAttrib->ModelScale;
}

//--------------------------------------------------------------
ofVec3f* SimpleObject::getScaleRef(){
	return &pAttrib->ModelScale;
}

void SimpleObject::SelectedInEditor(bool selected){
    bSelectedInEditor = selected;
}


//--------------------------------------------------------------
SimpleObjectAttrib * SimpleObject::getSimpleAttrib(){
    return pAttrib;
}

//--------------------------------------------------------------
ofxBulletBaseShape* SimpleObject::getSimpleBody(){
    return poSimpleBody;
}

//--------------------------------------------------------------
FreeTransformObject* SimpleObject::getFreeTransform(){
    return &oFreeTransform;
}