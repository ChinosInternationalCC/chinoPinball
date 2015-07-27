//
//  Gravity.cpp
//  chinoPinball
//
//  Created by Ovidiu on 9/5/15.
//
//

#include "Gravity.h"

Gravity::Gravity(vector <SimpleMission *> * _currentMissions)
: Obstacle(_currentMissions){
    changedGravity = ofVec3f(0, -30, 50);
    gravityChangeDuration = 10000; // ms
	changeGravity = false;
    m_bGravityObjectActive = false;
}

//--------------------------------------------------------------
void Gravity::setupSpecific(){
    type = ShapeTypeGravity;
   
}

//--------------------------------------------------------------
string Gravity::getObjectName(){
    return "Gravity";
}


//--------------------------------------------------------------
void Gravity::updateSpecific(bool bEditorMode) {
    if (changeGravity) {
        //world->setGravity(changedGravity);
    }
    else {
        //world->setGravity(normalGravity);
    }
}

//--------------------------------------------------------------
void Gravity::onCollisionSpecific(SimpleObject* Obj){
//    cout << idCurz`rtentMission << endl;
    if (m_bGravityObjectActive){
        normalGravity = world->getGravity();
        changeGravity = true;
    }
}

//--------------------------------------------------------------
void Gravity::ActivateGravityObject(bool gravityFlag){
    m_bGravityObjectActive = gravityFlag;
}

//--------------------------------------------------------------
bool Gravity::GetActiveGravityFlag(){
    return m_bGravityObjectActive;
}
//--------------------------------------------------------------
void Gravity::SetGravityChange(bool gravityChangeFlag){
    changeGravity = gravityChangeFlag;
    if(!gravityChangeFlag){

    //world->setGravity(normalGravity);
    }
}
