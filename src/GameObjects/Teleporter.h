//
//  Teleporter.h
//  chinoPinball
//
//  Created by Ovidiu on 9/5/15.
//
//

#pragma once

#include "Obstacle.h"

class Scenario;
class Teleporter : public Obstacle{
public:
    Teleporter(vector <SimpleMission *> * _currentMissions);
    void setupSpecific();
    void updateSpecific(bool bEditorMode);
    string getObjectName();
    void onCollisionSpecific(SimpleObject* Obj);
	
	void SetDetinationObjectId(int id);
    void SetDestinationObject(SimpleObject *object);
    
	void RegisterScenarioRef(Scenario *pScenario);
    void SetMultiBallStickyFlag(bool bFlag);
    bool GetMultiBallStickyFlag(void);
    bool IsBallStuck();
    void ReleaseBall();
    void ActivateTeleporter(bool activeFlag);
    bool GetTeleporterStatus();
private:
	Scenario *m_poScenario;
    SimpleObject *m_poDestinationObject;
    bool bSticky;//if this flag is true the ball will remain trapped when hitting the object
    int m_iBallStuckCount;
	int m_iDestinationObjectId;
    bool m_bTeleporterActive;
};