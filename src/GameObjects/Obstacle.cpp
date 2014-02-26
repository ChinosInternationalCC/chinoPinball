//
//  Obstacle.h
//  chinoPinball
//
//  Created by Angel on 02/02/14.
//
//

#include "Obstacle.h"

//---------------------------------
void Obstacle::setup(ofxBulletWorldRigid &world, ofVec3f position, string url){
    type = ShapeTypeObstacle;
    collisionTime = -120;
    
    this->position = position;
    rotation = btQuaternion(btVector3(0,1,0), ofDegToRad(-90));
    
    //to try with ofBtGetCylinderCollisionShape, for improve collision detection
    
    // load 3D model
    ofVec3f scale(0.05, 0.05, 0.05);
	assimpModel.loadModel(url, true);
	assimpModel.setScale(scale.x, scale.y, scale.z);
	assimpModel.setPosition(0, 0, 0);
    
    
    // add 3D mashes to ofxBullet shape
    for(int i = 0; i < assimpModel.getNumMeshes(); i++)
    {
        body.addMesh(assimpModel.getMesh(i), scale, true);
    }
    //    body.addMesh(assimpModel.getMesh(0), scale, true);
    
    // create ofxBullet shape
    body.create(world.world, position, 0); // we set m=0 for kinematic body
    body.add();
    body.enableKinematic();
    body.setProperties(.99, .05); // .25 (more restituition means more energy) , .95 ( friction )
    
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
    
    
}

//--------------------------------------------------------------
void Obstacle::draw(){
	
	int t = ofGetElapsedTimef()*100-collisionTime;
    if(t<120){
        ofSetColor(255, 0, 255);
    }else{
        ofSetColor(255, 255, 255);
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
    collisionTime = ofGetElapsedTimef()*100;

}


//--------------------------------------------------------------
void Obstacle::reset() {}

