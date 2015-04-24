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
	virtual void draw(bool bEditorMode);
	
	void autoScalingXYZ();
	void setupRot();
	
	ofxBulletCustomShape	body;
    
	ofVec3f         initScale;
    
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void setAnimation(bool bAnimate);
    void onCollision();
    void setDefaultZ();
    void setPosition(ofVec3f position);
	void setRotation(ofQuaternion rotation);
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
    
};
