//
//  Teleporter.h
//  chinoPinball
//
//  Created by Ovidiu on 9/5/15.
//
//

#pragma once

#include "Obstacle.h"

class Teleporter : public Obstacle{
public:
    Teleporter(vector <SimpleMission *> * _currentMissions);
    void setupSpecific();
    void updateSpecific(bool bEditorMode);
    string getObjectName();
    void onCollisionSpecific();
    void SetDestinationObject(SimpleObject &object);
private:
    SimpleObject *m_poDestinationObject;
};