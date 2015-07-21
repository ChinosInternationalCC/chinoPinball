//
//  Gravity.h
//  chinoPinball
//
//  Created by Ovidiu on 9/5/15.
//
//

#pragma once

#include "Obstacle.h"

class Gravity : public Obstacle {
public:
    Gravity(vector <SimpleMission *> * _currentMissions);
    void setupSpecific();
    void updateSpecific(bool bEditorMode);
    string getObjectName();
    void onCollisionSpecific(SimpleObject *Obj);
    ofVec3f normalGravity;
    ofVec3f changedGravity;
    
private:
    int gravityChangeDuration;
    double gravityChangeTimer;
	bool changeGravity;
    
};