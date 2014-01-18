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
	void rotate(float angle);

	ofxBulletCustomShape	body;
	ofxAssimpModelLoader	assimpModel;
    ofMaterial				material;
    
    
    

	ofVec3f position;

	float lowerLimit;
	float upperLimit;
    float speed;
    float axisX;
    
	void keyPressed(ofKeyEventArgs& key);
	void keyReleased(ofKeyEventArgs& key);
    bool isKeyPressed;

};
