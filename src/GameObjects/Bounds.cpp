//
//  Bounds.cpp
//  chinoPinball
//
//  Created by Angel Muc on 20/06/14.
//
//

#include "Bounds.h"

Bounds::Bounds(vector <SimpleMission *> * _currentMissions) :
    SimpleObject(_currentMissions)
{
    
}

//---------------------------------
void Bounds::setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale){
    type = ShapeTypeBounds;
    collisionTime = -120;
    ModelPath = url;
    this->position = position;
   // rotation = btQuaternion(btVector3(0,1,0), ofDegToRad(90));
    
    //to try with ofBtGetCylinderCollisionShape, for improve collision detection
    
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
	
	
    // add 3D mashes to ofxBullet shape
    for(int i = 0; i < assimpModel.getNumMeshes(); i++)
    {
        body.addMesh(assimpModel.getMesh(i), scale, true);
    }
	
    //    body.addMesh(assimpModel.getMesh(0), scale, true);

    assimpModel.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    assimpModel.playAllAnimations();
    body.add();
    
    //material.setAmbientColor(ofFloatColor(0, 0, 0));
	//material.setDiffuseColor(ofFloatColor(150, 0, 150));
	//material.setSpecularColor(ofFloatColor(220, 0, 220));
	//material.setShininess(40);
    
    
    body.enableKinematic();
    //body.setProperties(1., 0.); // .25 (more restituition means more energy) , .95 ( friction )
    // to add force to the ball on collision set restitution to > 1
	body.setProperties(.95, .5); // restitution, friction
	body.setDamping( .45 );
  
	/*
    
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
    */
	
	setupRot();
	
    body.activate();
    
}

//--------------------------------------------------------------
void Bounds::update(bool bEditorMode){
    
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
	
	//Update Physic work rotation if GUI change it
//	if(rotation != last_rotation){
//		setRotation(rotation);
//		last_rotation = rotation;
//	}
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
	
    
}
/*
 //--------------------------------------------------------------
 void Bounds::autoScalingXYZ(){
 
 }*/

//--------------------------------------------------------------
void Bounds::autoScalingXYZ(){
	
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
void Bounds::draw(bool bEditorMode){
	
	//if(bEditorMode){
		//>>??
		int t = ofGetElapsedTimef()*100-collisionTime;
		if(t<highlightTime){
			ofSetHexColor(highlightColor);
		}else{
			ofSetHexColor(color);
		}
		//<<??
		
	material.begin();
		body.transformGL();
		ofPoint scale = assimpModel.getScale();
		ofScale(scale.x,scale.y,scale.z);
		
		assimpModel.getMesh(0).drawFaces();
		
		body.restoreTramsformGL();
	material.end();
	//}
}

//-------------------------------------------------------------
ofxBulletBaseShape* Bounds::getBulletBaseShape(){
    return (ofxBulletBaseShape*)&body;
}

//------------------------------------------------------------
string Bounds::getObjectName(){
    return "Obstacle";
}

//------------------------------------------------------------
void Bounds::onCollision(){
    
    /*GameStatus::getInstance()->AddPoints(1);
    //save time to show color during some time
    collisionTime = ofGetElapsedTimef()*100;
    //play sound
    SoundManager::getInstance()->PlaySound(0);
    
	//Play rele //TODO After try to move this to SimpleObject ... then all objects will
	eventComunication newComEvent;
	newComEvent.collision = true;
    newComEvent.pObject = this;
	ofNotifyEvent(eventComunication::onNewCom, newComEvent);*/
}

//------------------------------------------------------------
void Bounds::setDefaultZ(){
    
    position.z = -0.5;
    setPosition(position);
    
}

//------------------------------------------------------------
void Bounds::setPosition(ofVec3f position){
    
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
void Bounds::setRotation(ofQuaternion rotation){
	
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
	
	body.activate();
    
}

//--------------------------------------------------------------
void Bounds::setupRot(){
	btTransform transform;
	btRigidBody* a_rb = body.getRigidBody();
	a_rb->getMotionState()->getWorldTransform( transform );
	
	btQuaternion currentRotation = transform.getRotation();
	rotation.set(currentRotation.x(), currentRotation.y(), currentRotation.z(), currentRotation.w());
    last_rotation = rotation;
	//Save angle Val too
	angleValX = last_angleValX;
	angleValY = last_angleValY;
	angleValZ = last_angleValZ;
	
	transform.setRotation(currentRotation);
	a_rb->getMotionState()->setWorldTransform( transform );

	body.activate();
}

//--------------------------------------------------------------
void Bounds::setAngle2Rotate(float angle2rot, ofVec3f axis2rot) {
	
	/*
	btRigidBody* a_rb = body.getRigidBody();
	btTransform transform;
    
	ofVec3f pos = body.getPosition();
	transform.setOrigin( btVector3(btScalar(pos.x), btScalar(pos.y), btScalar(pos.z)) );
	
	ofQuaternion rotQuat = body.getRotationQuat();
	
	btQuaternion rotate;// = btQuaternion(btVector3(axis2rot.x,axis2rot.y,axis2rot.z), ofDegToRad(angle2rot));
	rotate.setEuler(ofDegToRad(0), ofDegToRad(90), ofDegToRad(0));
	
	btQuaternion rotation = btQuaternion( btVector3(rotQuat.x(), rotQuat.y(), rotQuat.z() ) ,  angle2rot);
	transform.setRotation(rotate * rotation);
	
	a_rb->getMotionState()->setWorldTransform(transform);
	
	body.activate();
	*/
	
	/*
	btRigidBody* a_rb = body.getRigidBody();
	btTransform trans = body.getRigidBody()->getCenterOfMassTransform();
	btQuaternion transrot = trans.getRotation();
	
	btQuaternion rotquat;
	rotquat = rotquat.getIdentity();
	rotquat.setX((btScalar)angle2rotx);
	rotquat.setY((btScalar)angle2roty);
	rotquat.setZ((btScalar)angle2rotz);
	
	transrot = transrot * rotquat;
	
	trans.setRotation(transrot);
	
	//body.getRigidBody()->setCenterOfMassTransform(trans);
	
	//a_rb->getMotionState()->setWorldTransform( trans );
	
	body.activate();
*/
	
	
	 
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
	 
	
	
	/*
	btTransform transform;
	btRigidBody* a_rb = body.getRigidBody();
	a_rb->getMotionState()->getWorldTransform( transform );
	
	//Get actual Rotation
	//ofQuaternion obj_rotation = rotation;
	
	rotation.set(transform.getRotation().x(), transform.getRotation().y(), transform.getRotation().z(), transform.getRotation().w());
	
	
	cout << "Actual rotation \n" << rotation << endl;
	//cout << "rotation" << rotation << endl;
	//cout << "rotation" << rotation << endl;
	
	//Apply angle rotation
	rotation.makeRotate(angle2rot, axis2rot);
	
	//Save Rotation
	btQuaternion quaternionResult;
	quaternionResult.setValue(rotation.x(), rotation.y(), rotation.z(), rotation.w());
	
	//rotation.set(quaternionResult.x(), quaternionResult.y(), quaternionResult.z(), quaternionResult.w());
	//cout << "quaternionResult \n" << rotation << endl;
	
	//Apply Transform to the object
	transform.setRotation(quaternionResult);
	a_rb->getMotionState()->setWorldTransform( transform );
	
	body.activate();
	*/
	

	


	
	
}

