//
//  LeverKinematic.h
//  chinoPinball
//
//  Created by Kuba on 10/01/14.
//
//

#include "SimpleObject.h"

class LeverKinematic : public SimpleObject {
    
public:
	
	virtual void setup(ofxBulletWorldRigid &world);
	virtual void update();
	virtual void draw();
	void rotateLever(float a_yaw, float a_pitch, float a_roll);
	
	void applyPushLeft();
	
	void keyPressed(ofKeyEventArgs& key);
	void keyReleased(ofKeyEventArgs& key);
    
	ofxBulletBox	body;
    
	
	float lowerLimit;
	float upperLimit;
    float speed;    // degrees per frame
    
    bool isKeyPressed;
    
};