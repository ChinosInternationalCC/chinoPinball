//
//  Lever.h
//  chinoPinball
//
//  Created by Kuba on 03/01/14.
//
//

#include "ofxBullet.h"

class Lever : public ofxBulletBox {
    
public:
	void setup(ofxBulletWorldRigid &world);
	void update();
	void draw();
    
    ofxBulletJoint joint;
    
};