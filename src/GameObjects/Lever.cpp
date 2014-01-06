//
//  Lever.cpp
//  chinoPinball
//
//  Created by Kuba on 03/01/14.
//
//

#include "Lever.h"

//---------------------------------
void Lever::setup(ofxBulletWorldRigid &world){
    
    body.create(world.world, ofVec3f(3, 4, 0), 0.05, 4, .5, .5); // we set m=0 for a kinematic object
    body.add();
    
    joint.create( world.world, &body, ofVec3f(4.5, 4, 0));
    joint.setAngularLowerLimit(0, 0, 4.5);
    joint.setAngularUpperLimit(0, 0, 0.5);
    joint.add();

}

//--------------------------------------------------------------
void Lever::update(){
}

//--------------------------------------------------------------
void Lever::draw(){
    
	ofSetColor(0, 255, 0);
    body.draw();
    
}

