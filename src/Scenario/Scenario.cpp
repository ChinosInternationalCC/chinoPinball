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
    
    //m_sphere.setup(world);
    m_Ball.setup(world);
    leverLeft.setup(world);
    
}

//--------------------------------------------------------------
void Scenario::update(){
}

//--------------------------------------------------------------
void Scenario::draw(){
    
    //m_sphere.draw();
    m_Ball.draw();
    leverLeft.draw();
    
}