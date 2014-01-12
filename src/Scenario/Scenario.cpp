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
    
    m_Ball.setup(world,ofVec3f(2,0,0));
    m_Ball2.setup(world,ofVec3f(7,-6,0));
    leverLeft.setup(world);
    m_Hammer.setup(world,ofVec3f(7,4,0));
    
}

//--------------------------------------------------------------
void Scenario::update(){
	leverLeft.update();
    m_Hammer.update();
}

//--------------------------------------------------------------
void Scenario::draw(){
    
    m_Ball.draw();
    m_Ball2.draw();
    leverLeft.draw();
    m_Hammer.draw();
    
}