//
//  Bounds.h
//  chinoPinball
//
//  Created by Angel Muc on 20/06/14.
//
//

#pragma once

#include "eventComunication.h"
#include "SimpleObject.h"
#include "GameStatus.h"
#include "SoundManager.h"
#include "SimpleObject.h"


class Bounds : public SimpleObject {
    
public:
    
    Bounds(vector <SimpleMission *> * _currentMissions);
    
	virtual void setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale);
	virtual void update(bool bEditorMode);
	virtual void draw(bool bEditorMode);
	

	ofxBulletCustomShape	body;
    ofMesh                  assimpModelMesh;
	ofVec3f         initScale;

    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void onCollision();
    void setDefaultZ();
	void autoScalingXYZ();

    void setPosition(ofVec3f position);

	void setupRot();
	void setRotation(ofQuaternion rotation);
	
	//void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);
	void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);
    
};
