//
//  Obstacle.h
//  chinoPinball
//
//  Created by Angel on 02/02/14.
//
//

#pragma once

#include "eventComunication.h"
#include "SimpleObject.h"
#include "GameStatus.h"
#include "SoundManager.h"
#include "SimpleObject.h"


class Obstacle : public SimpleObject {

public:

    Obstacle(vector <SimpleMission *> * _currentMissions);
	
    void setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale);
	void update(bool bEditorMode);
    void draw(bool bEditorMode);
	
	void autoScalingXYZ();
	void setupRot();
	
	ofxBulletCustomShape	body;
    ofxBulletWorldRigid *m_poWorld;
    
	ofVec3f         initScale;


    ofxBulletBaseShape* getBulletBaseShape();
    virtual string getObjectName();
    
    void onCollision();
    void setDefaultZ();
    void setPosition(ofVec3f position);
	void setRotation(ofQuaternion rotation);
	void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);
	
	void setDefaultPostion();
    
protected:
    virtual void setupSpecific();
    virtual void updateSpecific(bool bEditorMode);
    virtual void onCollisionSpecific();
};
