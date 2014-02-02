//
//  Obstacle.h
//  chinoPinball
//
//  Created by Angel on 02/02/14.
//
//

#include "Obstacle.h"

//---------------------------------
void Obstacle::setup(ofxBulletWorldRigid &world, ofVec3f setPosition, string url){
    
    world.enableCollisionEvents();
	ofAddListener(world.COLLISION_EVENT, this, &Obstacle::onCollision);

    
    position = setPosition;
    
    rotation = btQuaternion(btVector3(0,1,0), ofDegToRad(-90));
    
    // load 3D model
    ofVec3f scale(0.1, 0.1, 0.1);
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
	
	ofSetColor(255, 255, 255);
	
    material.begin();
	
    body.transformGL();
    ofPoint scale = assimpModel.getScale();
    ofScale(scale.x,scale.y,scale.z);
    assimpModel.getMesh(0).drawFaces();
    body.restoreTramsformGL();
    
	material.end();
	
}

//--------------------------------------------------------------
void Obstacle::onCollision(ofxBulletCollisionData& cdata) {
	
		if(body == cdata) {
			//bColliding[i] = true;
            ofLog(OF_LOG_NOTICE, "collision TRUE");
            GameStatus::getInstance()->AddPoints(1);
		}else{
            ofLog(OF_LOG_NOTICE, "collision FALSE");
        }
	
}



