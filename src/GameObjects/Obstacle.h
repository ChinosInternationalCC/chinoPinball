//
//  Obstacle.h
//  chinoPinball
//
//  Created by Angel on 02/02/14.
//
//

#pragma once

#include "SimpleObject.h"
#include "GameStatus.h"
#include "SoundManager.h"

class Obstacle : public SimpleObject {

public:

	virtual void setup(ofxBulletWorldRigid &world, ofVec3f position, string url);
	virtual void update();
	virtual void draw();
    
	ofxBulletCustomShape	body;
	ofxAssimpModelLoader	assimpModel;
    ofMaterial				material;
    
    //vector<bool>				bColliding;
    
    
	//ofVec3f         position;
    
    btQuaternion    rotation;
    
    float angle; // degrees

    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void onCollision();
    void setDefaultZ();
    void setPosition(ofVec3f position);

};
