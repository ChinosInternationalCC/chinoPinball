//
//  Obstacle.cpp
//  chinoPinball
//
//  Created by Angel on 02/02/14.
//
//

#include "Obstacle.h"

//---------------------------------
void Obstacle::setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale){
    type = ShapeTypeObstacle;
    collisionTime = -120;
    ModelPath = url;
    this->position = position;
    rotation = btQuaternion(btVector3(0,1,0), ofDegToRad(-90));
    
    //to try with ofBtGetCylinderCollisionShape, for improve collision detection
    
    // create ofxBullet shape
    body.create(world.world, position, 0); // we set m=0 for kinematic body

    
    
    // load 3D model
    //ofVec3f scale(0.05, 0.05, 0.05);
    //scale = ofVec3f(0.005, 0.005, 0.005);
    scale = ModelScale;
	assimpModel.loadModel(url, true);
	assimpModel.setScale(scale.x, scale.y, scale.z);
	assimpModel.setPosition(0, 0, 0);

    
    // add 3D mashes to ofxBullet shape
    for(int i = 0; i < assimpModel.getNumMeshes(); i++)
    {
        body.addMesh(assimpModel.getMesh(i), scale, true);
    }
    //    body.addMesh(assimpModel.getMesh(0), scale, true);
    
    body.add();
    body.enableKinematic();
    //body.setProperties(1., 0.); // .25 (more restituition means more energy) , .95 ( friction )
	body.setProperties(.4, .75);
	body.setDamping( .25 );
    
    btTransform transform;
    btRigidBody* a_rb = body.getRigidBody();
    a_rb->getMotionState()->getWorldTransform( transform );
    
    // rotate
    //    btQuaternion currentRotation = transform.getRotation();
    //    btQuaternion rotate = btQuaternion(btVector3(0,0,1), ofDegToRad(degrees));
    btQuaternion rotate;
    
    //    rotation.setRotation(btVector3(0,0,1), ofDegToRad(angle));
    rotate.setEuler(ofDegToRad(0), ofDegToRad(90), ofDegToRad(0));
    transform.setRotation(rotate * rotation);
    
    a_rb->getMotionState()->setWorldTransform( transform );
    
    body.activate();
    

    
}

//--------------------------------------------------------------
void Obstacle::update(){
	cout << "update SimpleObject Obstacle";
	
	if (scaleXyz != last_scaleXyz) {
		float diff = last_scaleXyz - scaleXyz;
		last_scaleXyz = scaleXyz;
		//Apply diff to actual model
		scale = scale + diff;
	}
	else if(scale != last_scale){
		assimpModel.setScale(scale.x, scale.y, scale.z);
		last_scale = scale;
	}

    
}

//--------------------------------------------------------------
void Obstacle::draw(){
	
	int t = ofGetElapsedTimef()*100-collisionTime;
    if(t<highlightTime){
        ofSetHexColor(highlightColor);
    }else{
        ofSetHexColor(color);
    }
    
    //ofLog(OF_LOG_NOTICE, ofToString(t));
	
    material.begin();
	
    body.transformGL();
    ofPoint scale = assimpModel.getScale();
    ofScale(scale.x,scale.y,scale.z);
    assimpModel.getMesh(0).drawFaces();
    body.restoreTramsformGL();
    
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
    
    GameStatus::getInstance()->AddPoints(1);
    //save time to show color during some time
    collisionTime = ofGetElapsedTimef()*100;
    //play sound
    SoundManager::getInstance()->PlaySound(0);
   
	//Play rele //TODO After try to move this to SimpleObject ... then all objects will
	eventComunication newComEvent;
	newComEvent.collision = true;
    newComEvent.pObject = this;
	ofNotifyEvent(eventComunication::onNewCom, newComEvent);
}

//------------------------------------------------------------
void Obstacle::setDefaultZ(){
    
    position.z = -0.5;
    setPosition(position);
    
}

//------------------------------------------------------------
void Obstacle::setPosition(ofVec3f position){
    
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


