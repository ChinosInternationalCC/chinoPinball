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
	void rotate(float a_yaw, float a_pitch, float a_roll);
	
	void keyPressed(ofKeyEventArgs& key);
	void keyReleased(ofKeyEventArgs& key);
    
	ofxBulletBox	body;
    
	float lowerLimit;
	float upperLimit;
    float speed;   
    
    bool isKeyPressed;
    
};