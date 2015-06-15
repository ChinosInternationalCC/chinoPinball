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
    
    
    void SetMultiBallStickyFlag(bool bFlag);
    bool GetMultiBallStickyFlag(void);
    bool IsBallStuck();
    void ReleaseBall();
private:
    SimpleObject *m_poDestinationObject;
    bool bSticky;//if this flag is true the ball will remain trapped when hitting the object
    bool bBallStuck;
};