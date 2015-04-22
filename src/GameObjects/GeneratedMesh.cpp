//
//  AnimatedObject.cpp
//  chinoPinball
//
//  Created by Ovidiu on 16/4/15.
//
//

#include "GeneratedMesh.h"

GeneratedMesh::GeneratedMesh(vector <SimpleMission *> * _currentMissions) :
SimpleObject(_currentMissions)
{
    collisionPoints = 0;
    world = NULL;
}

//---------------------------------
void GeneratedMesh::setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale){
    type = ShapeTypeAnimatedMesh;
    collisionTime = -120;
    ModelPath = url;
    this->position = position;
    this->world = &world;
	
    //rotation = btQuaternion(btVector3(0,1,0), ofDegToRad(-90));
    
    //TODO to try with ofBtGetCylinderCollisionShape, for improve collision detection
    
    
    anisotropy = 4.;
    
    float fboDiv = 4.f;
    //    ofSetMinMagFilters( GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR );
    fbo.allocate( (float)ofGetWidth() / fboDiv, (float)ofGetWidth() / fboDiv, GL_RGB, 4 );
    fbo.begin(); {
        ofClear(0, 0, 0, 255 );
        ofSetColor( 11,90,121, 255);
        ofRect(0, 0, ofGetWidth(), ofGetHeight() );
        ofSetColor(120, 140, 150, 255);
        
        int numIterations = 4;
        float inc = (float)fbo.getWidth() / ((float)numIterations);
        for( int i = 0; i < numIterations; i++ ) {
            float tx = (float)i*inc + inc;
            float ty = (float)i*inc + inc;
            
            ofSetColor(152,197,190, 255);
            ofSetLineWidth( 1.5 );
            if( i % 2 == 0 ) ofSetLineWidth( 0.5 );
            
            ofLine( tx, 0, tx, fbo.getHeight() );
            ofLine( 0, ty, fbo.getWidth(), ty );
        }
        
    } fbo.end();
    
    ofSetLineWidth( 1 );
    
    fbo.getTextureReference().bind();
    glGenerateMipmap( fbo.getTextureReference().texData.textureTarget);
    ofSetMinMagFilters( GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
    //    glSamplerParameterf( fbo.getTextureReference().texData.textureTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2 );
    fbo.getTextureReference().unbind();

    
    omesh = ofMesh::plane( 70, 70, 14, 14, OF_PRIMITIVE_TRIANGLES );
    ofQuaternion rquat;
    rquat.makeRotate( 90, 1, 0, 0);
    ofSeedRandom();
    float rseed = ofRandom(0, 10000);
    vector< ofVec3f >& verts = omesh.getVertices();
    for( int i = 0; i < verts.size(); i++ ) {
        verts[i] = rquat * verts[i];
        verts[i].y = ofSignedNoise( verts[i].x*0.02, verts[i].y*0.02 + verts[i].z*0.02, ofGetElapsedTimef() * 0.1 + rseed ) * 3;
    }
    
    vector< ofVec2f >& tcoords = omesh.getTexCoords();
    for( int i = 0; i < tcoords.size(); i++ ) {
        tcoords[i].x *= 4.f;
        tcoords[i].y *= 4.f;
    }
    mesh = omesh;
    
    
    //ofEnableSeparateSpecularLight();
    
	//save init values
	initScale = scale;
    // create ofxBullet shape
    //body.create(world.world, position, 0); // we set m=0 for kinematic body
    body.create( world.world, mesh, position, 0.f, ofVec3f(-10000, -10000, -10000), ofVec3f(10000,10000,10000) );
    body.add();
    body.enableKinematic();
    body.setActivationState( DISABLE_DEACTIVATION );
    
    
    bAnimate = true;

    body.add();
    
	
    //body.setProperties(1., 0.); // .25 (more restituition means more energy) , .95 ( friction )
    // to add force to the ball on collision set restitution to > 1
	
	body.setProperties(3, .95); // restitution, friction
	body.setDamping( .25 );
    
	
	//Set Rotation Objects
	setupRot();
	
    body.activate();
	
	setDefaultZ();
    

    
    
    
}


//--------------------------------------------------------------
void GeneratedMesh::update(bool bEditorMode){
    
	autoScalingXYZ();

    
    
    
    
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
    
    if(bAnimate) {
        vector< ofVec3f >& verts = mesh.getVertices();
        vector< ofVec3f >& overts = omesh.getVertices();
        for( int i = 0; i < verts.size(); i++ ) {
            verts[i].y = ofSignedNoise( verts[i].x*0.025, verts[i].y*0.025 + verts[i].z*0.025, ofGetElapsedTimef() * 0.75 ) * 3;
        }
        body.updateMesh( this->world->world, mesh );
    }
    
    //world.update( ofGetLastFrameTime(), 12 );

	body.activate();
    
}
/*
 //--------------------------------------------------------------
 void Obstacle::autoScalingXYZ(){
 
 }*/

//--------------------------------------------------------------
void GeneratedMesh::autoScalingXYZ(){
	
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
	
	}
    
}

//--------------------------------------------------------------
void GeneratedMesh::draw(bool bEditorMode){
	
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
    body.transformGL();
    
    ofSetColor( 255, 255, 255, 255 );
    fbo.getTextureReference().bind();
    glSamplerParameterf( fbo.getTextureReference().texData.textureTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy );
    ofSetTextureWrap( GL_REPEAT, GL_REPEAT );
    mesh.draw();
    fbo.getTextureReference().unbind();
    
    body.restoreTramsformGL();
#if 0
	material.begin();
    
	ofPoint scaleModel		= assimpModel.getScale();
    
    mesh = assimpModel.getCurrentAnimatedMesh(0);
    body.updateMesh( this->world->world, mesh );
    body.getRigidBody()->getCollisionShape()->setLocalScaling(btVector3(scaleModel.x, scaleModel.y,  scaleModel.z));
    
    body.transformGL();
    ofScale(scaleModel.x,scaleModel.y,scaleModel.z);
    //assimpModel.getMesh(0).drawFaces();
    //assimpModel.getMesh(0).drawWireframe();
    //if (ModelPath.compare(_sysPath) == 0)
    //    ofRotateX(90);
    
    
    mesh.drawWireframe();
    
    
	body.restoreTramsformGL();
    
	glPopAttrib();
	material.end();
#endif
}
//-------------------------------------------------------------
ofxBulletBaseShape* GeneratedMesh::getBulletBaseShape(){
    return (ofxBulletBaseShape*)&body;
}

//------------------------------------------------------------
string GeneratedMesh::getObjectName(){
    return "GeneratedMesh";
}

//------------------------------------------------------------
void GeneratedMesh::onCollision(){
    
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
void GeneratedMesh::setDefaultZ(){
    
    position.z = -0.511;
    setPosition(position);
    
}

//------------------------------------------------------------
void GeneratedMesh::setPosition(ofVec3f position){
    
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
void GeneratedMesh::setRotation(ofQuaternion rotation){
    
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
void GeneratedMesh::setupRot(){
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
void GeneratedMesh::setAngle2Rotate(float angle2rot, ofVec3f axis2rot) {
	
	
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


