//
//  AnimatedObject.cpp
//  chinoPinball
//
//  Created by Ovidiu on 16/4/15.
//
//

#include "AnimatedObject.h"
string sysPath = "Sysiphous/sysiphus_centred.dae";

AnimatedObject::AnimatedObject(vector <SimpleMission *> * _currentMissions) :
SimpleObject(_currentMissions)
{
    collisionPoints = 0;
}

//---------------------------------
void AnimatedObject::setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale){
    type = ShapeTypeAnimatedObject;
    collisionTime = -120;
    ModelPath = url;
    this->position = position;
	
    //rotation = btQuaternion(btVector3(0,1,0), ofDegToRad(-90));
    
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
   // for(int i = 0; i < assimpModel.getNumMeshes(); i++)
   // {
        body.addMesh(assimpModel.getCurrentAnimatedMesh(0), scale, true);
   // }
    
    bAnimate = true;
    assimpModel.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    assimpModel.playAllAnimations();
    body.add();
    
	
    body.enableKinematic();
    //body.setProperties(1., 0.); // .25 (more restituition means more energy) , .95 ( friction )
    // to add force to the ball on collision set restitution to > 1
	
	body.setProperties(3, .95); // restitution, friction
	body.setDamping( .25 );
    
    // btTransform transform;
    //btRigidBody* a_rb = body.getRigidBody();
    //a_rb->getMotionState()->getWorldTransform( transform );
    
    // rotate
    //    btQuaternion currentRotation = transform.getRotation();
    //    btQuaternion rotate = btQuaternion(btVector3(0,0,1), ofDegToRad(degrees));
    //    btQuaternion rotate;
    
    //    rotation.setRotation(btVector3(0,0,1), ofDegToRad(angle));
    //   rotate.setEuler(ofDegToRad(0), ofDegToRad(90), ofDegToRad(0));
    //   transform.setRotation(rotate * rotation);
    
    //   a_rb->getMotionState()->setWorldTransform( transform );
	
	//Set Rotation Objects
	setupRot();
	
    body.activate();
	
	setDefaultZ();
    
    assimpPath.loadModel("Sysiphous/lineMesh.obj");
    assimpPath.setPosition(0, 0, 0);
    currentVetice = 0;
    
}


//--------------------------------------------------------------
void AnimatedObject::update(bool bEditorMode){
    
	autoScalingXYZ();
    
    assimpModel.update();
    
	//Udpate mesch if there are changes
	// add 3D mashes to ofxBullet shape
    //for(int i = 0; i < assimpModel.getNumMeshes(); i++)
    //{
    //btVector3 myBtScale;
    //myBtScale.setX(scale.x);
    //myBtScale.setY(scale.y);
    //myBtScale.setZ(scale.z);
    
    //body.getRigidBody()->getCollisionShape()->setLocalScaling(myObjectScale);//->m_collisionShape
    //setImplicitShapeDimensions(myBtScale);
    //addMesh(assimpModel.getMesh(i), scale, true);
    //}
	
	if(position.x != last_positionX){
		setPosition(position);
		last_positionX = position.x;
	}
	if(position.y != last_positionY){
		setPosition(position);
		last_positionY = position.y;
	}
	if(position.z != last_positionZ){
		setPosition(position);
		last_positionZ = position.z;
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
    
    assimpPath.update();
  /*
   
    if ( (currentVetice < assimpPath.getMesh(0).getNumVertices()) &&
         (ModelPath.compare(sysPath) == 0)
        ){
        ofVec3f pos = assimpPath.getMesh(0).getVertex(currentVetice);
        setPosition(ofVec3f(pos.x/100, pos.y/100, pos.z/100));
        currentVetice ++;
    }
    else
        currentVetice = 0;
	*/
	body.activate();
    
}
/*
 //--------------------------------------------------------------
 void Obstacle::autoScalingXYZ(){
 
 }*/

//--------------------------------------------------------------
void AnimatedObject::autoScalingXYZ(){
	
	btVector3 myObjectScale;
	ofVec3f myOfObjectScale;
	
	
	if (scaleXyz != last_scaleXyz) {
		float diff = scaleXyz - last_scaleXyz;
		last_scaleXyz = scaleXyz;
		
		//Get Scales
		myObjectScale = body.getRigidBody()->getCollisionShape()->getLocalScaling();
		myOfObjectScale = ofVec3f(myObjectScale.x(), myObjectScale.y(), myObjectScale.z());
        
		//Update sizes values
		myOfObjectScale += ofMap(diff, 0, initScale.z, 0, 0.45); //+= diff;
		scale += ofMap(diff, 0, initScale.z, 0, 0.025);
		last_scale = scale;
        
		myObjectScale.setX(myOfObjectScale.x);
		myObjectScale.setY(myOfObjectScale.y);
		myObjectScale.setZ(myOfObjectScale.z);
        
		//update physyc object
		body.getRigidBody()->getCollisionShape()->setLocalScaling(myObjectScale);
		assimpModel.setScale(scale.x, scale.y, scale.z);
	}
    
}

//--------------------------------------------------------------
void AnimatedObject::draw(bool bEditorMode){
	
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
    //assimpModel.getMesh(0).drawFaces();
    //assimpModel.getMesh(0).drawWireframe();
    assimpModel.getCurrentAnimatedMesh(0).drawWireframe();

    
	body.restoreTramsformGL();
    
	glPopAttrib();
	material.end();
    
}
//-------------------------------------------------------------
ofxBulletBaseShape* AnimatedObject::getBulletBaseShape(){
    return (ofxBulletBaseShape*)&body;
}

//------------------------------------------------------------
string AnimatedObject::getObjectName(){
    return "AnimatedObject";
}

//------------------------------------------------------------
void AnimatedObject::onCollision(){
    
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

//------------------------------------------------------------
void AnimatedObject::setDefaultZ(){
    
    position.z = -0.511;
    setPosition(position);
    
}

//------------------------------------------------------------
void AnimatedObject::setPosition(ofVec3f position){
    
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

//------------------------------------------------------------
void AnimatedObject::setRotation(ofQuaternion rotation){
    
    btTransform transform;
    btRigidBody* rigidBody = body.getRigidBody();
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
void AnimatedObject::setupRot(){
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
void AnimatedObject::setAngle2Rotate(float angle2rot, ofVec3f axis2rot) {
	
	
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

