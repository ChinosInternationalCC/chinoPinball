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
    
    //TODO to try with ofBtGetCylinderCollisionShape, for improve collision detection
    
    // create ofxBullet shape
    body.create(world.world, position, 0); // we set m=0 for kinematic body

    
    // load 3D model
    scale = ModelScale;
	assimpModel.loadModel(url, true);
	assimpModel.setScale(scale.x, scale.y, scale.z);
	assimpModel.setPosition(0, 0, 0);

    //ofEnableSeparateSpecularLight();
    
	//save init values
	initScale = scale;
	
	
    // add 3D meshes to ofxBullet shape
    for(int i = 0; i < assimpModel.getNumMeshes(); i++)
    {
        body.addMesh(assimpModel.getMesh(i), scale, true);
    }

    assimpModel.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    assimpModel.playAllAnimations();
    body.add();
    
	/*
    material.setAmbientColor(ofFloatColor(0, 0, 0));
	material.setDiffuseColor(ofFloatColor(150, 0, 150));
	material.setSpecularColor(ofFloatColor(220, 0, 220));
	material.setShininess(40);
    */
    
    body.enableKinematic();
    //body.setProperties(1., 0.); // .25 (more restituition means more energy) , .95 ( friction )
    // to add force to the ball on collision set restitution to > 1
	body.setProperties(3, .95); // restitution, friction
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
void Obstacle::update(bool bEditorMode){

    assimpModel.update();
    assimpModelMesh = assimpModel.getCurrentAnimatedMesh(0); // Animation Player
	
	body.activate();

}


//--------------------------------------------------------------
void Obstacle::draw(bool bEditorMode){
    
    
	
	//>>??
	int t = ofGetElapsedTimef()*100-collisionTime;
    if(t<highlightTime){
        ofSetHexColor(highlightColor);
    }else{
        ofSetHexColor(color);
    }
	//<<??

    
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
    glEnable(GL_NORMALIZE);
    glDisable(GL_CULL_FACE);
	ofPoint scaleModel		= assimpModel.getScale();
	
	body.transformGL();
    ofScale(scaleModel.x,scaleModel.y,scaleModel.z);
    assimpModel.getMesh(0).drawFaces();
	body.restoreTramsformGL();
	
	glPopAttrib();
	
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


