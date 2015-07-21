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
}

void Gravity::setupSpecific(){
    type = ShapeTypeGravity;
}

string Gravity::getObjectName(){
    return "Gravity";
}


void Gravity::updateSpecific(bool bEditorMode) {
    if (changeGravity) {
        if ((ofGetElapsedTimeMillis() - gravityChangeTimer) < gravityChangeDuration) {
            world->setGravity(changedGravity);
        }
        else {
            world->setGravity(normalGravity);
            changeGravity = false;
        }
    }
}


void Gravity::onCollisionSpecific(SimpleObject* Obj){
//    cout << idCurz`rtentMission << endl;
    normalGravity = world->getGravity();
	gravityChangeTimer = ofGetElapsedTimeMillis();
	changeGravity = true;
}
