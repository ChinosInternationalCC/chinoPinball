//
//  PinballChinoManager.h
//  chinoPinball
//
//  Created by Kuba on 28/12/13.
//
//

#include "ofMain.h"
#include "ofxBullet.h"

class PinballChinoManager {
    
public:
	void setup();
	void update();
	void draw();
    
    ofxBulletWorldRigid     world;
	ofCamera                camera;
};
