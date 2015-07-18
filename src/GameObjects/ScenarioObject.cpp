//
//  Obstacle.cpp
//  chinoPinball
//
//  Created by Carles Gutierrez on 17/07/15.
//
//

#include "ScenarioObject.h"



ScenarioObject::ScenarioObject(vector <SimpleMission *> * _currentMissions) :
    SimpleObject(&body, _currentMissions, -1.0)
{
    collisionPoints = 0;
}

//---------------------------------
void ScenarioObject::setup(ofxBulletWorldRigid &world,
                     SimpleObjectAttrib *Attributes){

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

void ScenarioObject::setupBody(SimpleObjectAttrib &Attributes){
	
	// create ofxBullet shape
	cout << "Scenario getPosition() = " << getPosition() << endl;
	
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
	
	body.setProperties(1, .95); // restitution, friction
	body.setDamping( .25 );
    
    
    body.activate();
}


//----------------------------------
void ScenarioObject::setupLookStyle(SimpleObjectAttrib &Attributes){
    //NOTHING
}

//----------------------------------
void ScenarioObject::setupAnimations(SimpleObjectAttrib &Attributes){
    
    collisionTime = -120;
}

//----------------------------------
void ScenarioObject::setupType(){
    type = ShapeTypeScenario;
}


//--------------------------------------------------------------
void ScenarioObject::setupSpecific(){
    //DO Nothing
}

//--------------------------------------------------------------
void ScenarioObject::updateSpecific(bool bEditorMode){
    //DO Nothing
}


//--------------------------------------------------------------
void ScenarioObject::draw(bool bEditorMode){
	
	/*
	int t = ofGetElapsedTimef()*100-collisionTime;
    if(bEditorMode && bSelectedInEditor){
        ofSetHexColor(highlightColor);
    }
    else if(t<highlightTime){
        ofSetHexColor(highlightColor);
    }else{
        if((*currentMissions)[idCurrtentMission]->isElementHit(GetObjectId())){
            ofSetHexColor(highlightColor);
        }
        else{
        ofSetHexColor(color);
        }
    }
	*/

	ofSetColor(ofColor::white);
	
	material.begin();

	ofPoint scaleModel = assimpModel.getScale();
	

	 body.transformGL();
	 ofScale(scaleModel.x,scaleModel.y,scaleModel.z);
     assimpModel.getMesh(0).drawFaces();
	 body.restoreTramsformGL();
	
	 glPopAttrib();
	 material.end();


}
//-------------------------------------------------------------
ofxBulletBaseShape* ScenarioObject::getBulletBaseShape(){
    return (ofxBulletBaseShape*)&body;
}

//------------------------------------------------------------
string ScenarioObject::getObjectName(){
    return "Scenario";
}

//------------------------------------------------------------
void ScenarioObject::onCollision(int ObjId){
    
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
void ScenarioObject::onCollisionSpecific(){
    //Do Nothing
}

//--------------------------------------------------------------
void ScenarioObject::setupRot(){
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
ScenarioObjectAttrib* ScenarioObject::getScenarioObjectAttr(){
    return (ScenarioObjectAttrib*) getSimpleAttrib();
}







