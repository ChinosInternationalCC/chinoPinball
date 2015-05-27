//
//  Bounds.cpp
//  chinoPinball
//
//  Created by Angel Muc on 20/06/14.
//
//

#include "Bounds.h"

Bounds::Bounds(vector <SimpleMission *> * _currentMissions) :
    SimpleObject(&body, _currentMissions, -0.5)
{
    
}

//---------------------------------
void Bounds::setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale){
    //position.z = -0.5;
    
    
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

	
	setupRot();
	
    body.activate();
    
    setDefaultZ();
    
}


//--------------------------------------------------------------
void Bounds::updateSpecific(bool bEditorMode){
	//TODO
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

