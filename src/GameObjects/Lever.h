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

    Lever(SimpleMission *currentMission);
	void setup(ofxBulletWorldRigid &world, ofVec3f setPosition, string url, ofVec3f ModelScale, int setDirection);

	void update(bool bEditorMode);
	void draw(bool bEditorMode);
	void rotate(float degrees);
    
	ofxBulletCustomShape	body;
	ofxAssimpModelLoader	assimpModel;
    ofMaterial				material;    
    
	//ofVec3f         position;
    int             direction; // rotation direction: 1 - clockwise, 0 - counter clockwise
    
    btQuaternion    rotation;
    
    float angle; // degrees
	float lowerLimit;
	float upperLimit;
    float speed;
    float axisX;
    
    bool isKeyPressed;
    void onMoveEvent();
    void onReleaseEvent();
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void onCollision();
    void setDefaultZ();
    void setPosition(ofVec3f position);


};
