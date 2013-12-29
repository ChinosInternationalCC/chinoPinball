//
//  Scenario.cpp
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//

#include "Scenario.h"

//--------------------------------------------------------------
void Scenario::setup(ofxBulletWorldRigid &world){
    
    ball.setup(world);
    
}

//--------------------------------------------------------------
void Scenario::update(){
}

//--------------------------------------------------------------
void Scenario::draw(){
    
    ball.draw();
    
}