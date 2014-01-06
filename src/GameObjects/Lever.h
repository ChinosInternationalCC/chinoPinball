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
	
	virtual void setup(ofxBulletWorldRigid &world);
	virtual void update();
	virtual void draw();
    
	ofxBulletBox	body;
    ofxBulletJoint joint;
	
	//ofxBulletSphere *           shape; // generic bullet shape object. it is a sphere only for testing.
    
    
};