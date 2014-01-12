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
    m_Hammer.setup(world);
    
}

//--------------------------------------------------------------
void Scenario::update(){
	leverLeft.update();
    m_Hammer.update();
}

//--------------------------------------------------------------
void Scenario::draw(){
    
    //m_sphere.draw();
    m_Ball.draw();
    leverLeft.draw();
    m_Hammer.draw();
    
}