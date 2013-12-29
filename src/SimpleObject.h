//
//  SimpleObject.h
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//

#include "ofxBullet.h"

class SimpleObject {
    
public:
	void setup(ofxBulletWorldRigid &world);
	void update();
	void draw();
    
    ofxBulletWorldRigid *       world;
    ofxBulletSphere *           shape; // generic bullet shape object. it is a sphere only for testing.
    
};