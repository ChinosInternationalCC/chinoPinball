//
//  Obstacle.h
//  chinoPinball
//
//  Created by Angel on 02/02/14.
//
//

#pragma once

#include "SimpleObject.h"

class Obstacle : public SimpleObject {

public:

	virtual void setup(ofxBulletWorldRigid &world, ofVec3f setPosition, string url);
	virtual void update();
	virtual void draw();
    
	ofxBulletCustomShape	body;
	ofxAssimpModelLoader	assimpModel;
    ofMaterial				material;
    
    
    
    
	ofVec3f         position;
    
    btQuaternion    rotation;
    
    float angle; // degrees

    

};
