//
//  AnimatedMotionPath.h
//  chinoPinball
//
//  Created by Ovidiu on 16/4/15.
//
//

#pragma once

#include "eventComunication.h"
#include "SimpleObject.h"
#include "GameStatus.h"
#include "SoundManager.h"
#include "SimpleObject.h"

/**
 *  DRAFT!!! This kind of objects are not working properly
 *
 *  The AnimatedMotionPath object is used to load a model that will be draw and another animated model
 *  that moves around o a certain path (a sphere for example). This animated object will define the position 
 *  of the obkect that will be draw.
 *  
 *  In the current implementation we have problems in recovering the correct transformation matrix from the 
 *  animated object and pass it to the object that it drawn. Initialy we were recovering only the position 
 *  but we also have to recover the scale and rotation of the animated objetc
 *
 */

class AnimatedMotionPath : public SimpleObject {
    
public:
    
    enum enMotionControl{
        MOTION_CONTROL_LOOP = 0,
        MOTION_CONTROL_MANUAL,
        MOTION_CONTROL_END_POINT
    };
    
    AnimatedMotionPath(vector <SimpleMission *> * _currentMissions);
	virtual void setup(ofxBulletWorldRigid &world, ofVec3f position, string url, string pathMotionModel,ofVec3f ModelScale);
	virtual void update(bool bEditorMode);
    void updateSpecific(bool bEditorMode);
	virtual void draw(bool bEditorMode);
	

	void setupRot();
	
	ofxBulletCustomShape	body;
    
	ofVec3f         initScale;
    
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void setAnimation(bool bAnimate);
    void onCollision();
	void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);
    
    void MotionPathPlay();
    void MotionPathStop();
    void MotionPathPause(bool paused);
    void MotionPathSetPosition(float position);
    void MotionPathSetAnimationEndPos(float position);
    void MotionPathMoveFW();
    void MotionPathMoveBK();
    void MotionPathIncrementAnimationEndPosition();
    
    
    string getMotionModelPath();
    
    void keyPressed(ofKeyEventArgs& args);
	void keyReleased(ofKeyEventArgs& args);
    
private:
    bool bAnimate;
    ofxAssimpModelLoader	assimpPath;
    string m_pathMotionModel;
    float m_bAnimationEndPos;
    float m_motionPathCurPos;
    enMotionControl m_eMotionControl;
    float m_fixedZ;
    int m_AnimationMeshNo;
};
