//
//  AAnimatedMotionPath.cpp
//  chinoPinball
//
//  Created by Ovidiu on 16/4/15.
//
//

#include "AnimatedMotionPath.h"
#include "AssimpUtils.h"


AnimatedMotionPath::AnimatedMotionPath(vector <SimpleMission *> * _currentMissions) :
SimpleObject(&body, _currentMissions, -0.511)
{
    collisionPoints = 0;
    
}

//---------------------------------
void AnimatedMotionPath::setup(ofxBulletWorldRigid &world, ofVec3f position, string url, string pathMotionModel, ofVec3f ModelScale){
    // position.z = -0.511;

    
    type = ShapeTypeAnimatedMotionPath;
    collisionTime = -120;
    ModelPath = url;
    m_pathMotionModel = pathMotionModel;
    this->position = position;
    m_fixedZ = position.z;
	m_AnimationMeshNo = 1;
    
    //rotation = btQuaternion(btVector3(0,1,0), ofDegToRad(-90));
    
    //TODO to try with ofBtGetCylinderCollisionShape, for improve collision detection
    
    // create ofxBullet shape
    body.create(world.world, position, 0); // we set m=0 for kinematic body
    
    
    // load 3D model
    scale = ModelScale;
	assimpModel.loadModel(url, true);
	assimpModel.setScale(scale.x, scale.y, scale.z);
	assimpModel.setPosition(0, 0, 0);
    assimpModel.update();
    
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

	
	//Set Rotation Objects
	setupRot();
	
    body.activate();
	
	setDefaultZ();
    
    assimpPath.loadModel(m_pathMotionModel);
    assimpPath.setPosition(0, 0, 0);
    assimpPath.setScale(scale.x, scale.y, scale.z);
    assimpPath.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    assimpPath.playAllAnimations();
    m_motionPathCurPos = assimpPath.getAnimation(m_AnimationMeshNo).getPosition();
    
    
    m_eMotionControl = MOTION_CONTROL_LOOP;
    
    ofRegisterKeyEvents(this);
    
}


//--------------------------------------------------------------
void AnimatedMotionPath::update(bool bEditorMode){
    
	autoScalingXYZ();
    
    assimpModel.update();
	
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

    /* Update the model position acording to the motion path */
    switch(m_eMotionControl){
        case MOTION_CONTROL_LOOP:
            assimpPath.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
            assimpPath.playAllAnimations();
            break;
        case MOTION_CONTROL_MANUAL:
            assimpPath.setPausedForAllAnimations(true);
            assimpPath.getAnimation(m_AnimationMeshNo).setPosition(m_motionPathCurPos);
            break;
        case MOTION_CONTROL_END_POINT:
            /* 
             check if the current animation position is not >= m_bAnimationEndPos
             and pause the animation until a new AnimationEndPos is given
             
             TODO the end of the model animation, should reloop?
             */
            if (m_motionPathCurPos >= m_bAnimationEndPos)
                 assimpPath.setPausedForAllAnimations(true);
            else
                assimpPath.setPausedForAllAnimations(false);
            break;
    }
    
    assimpPath.update();
    m_motionPathCurPos = assimpPath.getAnimation(m_AnimationMeshNo).getPosition();
    setPosition(AssimpUtils::getAnimatedObjectPosition(assimpPath));

	body.activate();
    
}
//--------------------------------------------------------------
void AnimatedMotionPath::updateSpecific(bool bEditorMode){
	//TODO
}


//--------------------------------------------------------------
void AnimatedMotionPath::draw(bool bEditorMode){
	
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
    //if (ModelPath.compare(sysPath) == 0)
    //   ofRotateX(90);
    ofxAssimpMeshHelper &modelMeshHelper = assimpModel.getMeshHelper(0);
    //assimpModel.getCurrentAnimatedMesh(0).drawWireframe();
    ofPushMatrix();
    //ofMultMatrix(modelMeshHelper.matrix);
    modelMeshHelper.vbo.drawElements(GL_LINES,modelMeshHelper.indices.size());
    ofPopMatrix();
    ofxAssimpMeshHelper &pathMeshHelper = assimpPath.getMeshHelper(m_AnimationMeshNo);
    //assimpPath.getCurrentAnimatedMesh(m_AnimationMeshNo).drawWireframe();
    ofPushMatrix();
    //ofMultMatrix(pathMeshHelper.matrix);
    pathMeshHelper.vbo.drawElements(GL_LINES,pathMeshHelper.indices.size());
    ofPopMatrix();
    assimpPath.drawWireframe();
	body.restoreTramsformGL();
    
	glPopAttrib();
	material.end();
    
}
//-------------------------------------------------------------
ofxBulletBaseShape* AnimatedMotionPath::getBulletBaseShape(){
    return (ofxBulletBaseShape*)&body;
}

//------------------------------------------------------------
string AnimatedMotionPath::getObjectName(){
    return "AnimatedMotionPath";
}

//------------------------------------------------------------
void AnimatedMotionPath::onCollision(){
    
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

//--------------------------------------------------------------
void AnimatedMotionPath::setupRot(){
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
void AnimatedMotionPath::setAngle2Rotate(float angle2rot, ofVec3f axis2rot) {
	
	
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

//------------------------------------------------------------
string AnimatedMotionPath::getMotionModelPath(){
    return m_pathMotionModel;
}

//------------------------------------------------------------
void AnimatedMotionPath::MotionPathPlay(){
    assimpPath.getAnimation(0).play();
}

//------------------------------------------------------------
void AnimatedMotionPath::MotionPathStop(){
    assimpPath.getAnimation(0).stop();
}

//------------------------------------------------------------
void AnimatedMotionPath::MotionPathPause(bool paused){
    assimpPath.getAnimation(0).setPaused(paused);
}

//------------------------------------------------------------
void AnimatedMotionPath::MotionPathSetPosition(float position){
    assimpPath.getAnimation(0).setPosition(position);
}

//------------------------------------------------------------
void AnimatedMotionPath::MotionPathSetAnimationEndPos(float position){
    m_bAnimationEndPos = position;
}


void AnimatedMotionPath::MotionPathMoveFW(){
    m_motionPathCurPos = m_motionPathCurPos + 0.01;
    if (m_motionPathCurPos >= 1){
        m_motionPathCurPos = 0;
    }
}

void AnimatedMotionPath::MotionPathMoveBK(){
    m_motionPathCurPos = m_motionPathCurPos - 0.01;
    if (m_motionPathCurPos <= 0){
        m_motionPathCurPos = 1;
    }
}

void AnimatedMotionPath::MotionPathIncrementAnimationEndPosition(){
    m_bAnimationEndPos = m_bAnimationEndPos + 0.2;
}

//------------------------------------------------------------
void AnimatedMotionPath::keyPressed  (ofKeyEventArgs& args){
    if(args.key == 'p'){
        MotionPathPlay();
	}
    else if (args.key == 'o'){
        MotionPathPause(true);
    }
    else if (args.key == 'i'){
        MotionPathStop();
    }
    else if (args.key == 'u'){
        m_eMotionControl = MOTION_CONTROL_MANUAL;
        MotionPathMoveFW();
    }
    else if (args.key == 'y'){
        m_eMotionControl = MOTION_CONTROL_MANUAL;
        MotionPathMoveBK();
    }
    else if (args.key == 't'){
        m_eMotionControl = MOTION_CONTROL_END_POINT;
        MotionPathIncrementAnimationEndPosition();
    }
}

//------------------------------------------------------------
void AnimatedMotionPath::keyReleased(ofKeyEventArgs& args){
    
}

