//
//  Lever.h
//  chinoPinball
//
//  Created by Kuba on 03/01/14.
//
//

#pragma once

#include "SimpleObject.h"


class Lever : public SimpleObject {
    
public:
    
    Lever(vector <SimpleMission *> * _currentMissions);
	void setup(ofxBulletWorldRigid &world, ofVec3f setPosition, string url, ofVec3f ModelScale, int setDirection);
    
	void update(bool bEditorMode);
	void draw(bool bEditorMode);
	void rotate(float degrees);
	
	void setupRot();
    
	ofxBulletCustomShape	body;
    
    
	//ofVec3f         position;
    int             direction; // rotation direction: 1 - clockwise, 0 - counter clockwise
    
    btQuaternion    rotationLever;
    
    float angle; // degrees
	float lowerLimit;
	float upperLimit;
    float speed, speedUp, speedDown;
    float axisX;
    
    bool isKeyPressed;
    void onMoveEvent();
    void onReleaseEvent();
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void onCollision();
    void setDefaultZ();
    void setPosition(ofVec3f position);
    void setRotation(ofQuaternion rotation);
    
    
};
