//
//  Ramp.h
//  chinoPinball
//
//  Created by carles on 10/05/15.
//
//

#pragma once

#include "Obstacle.h"

class Ramp : public Obstacle{
public:
	Ramp(vector <SimpleMission *> * _currentMissions);
	void setupSpecific();
	void updateSpecific(bool bEditorMode);
	string getObjectName();
	void onCollisionSpecific(SimpleObject* Obj);

private:
	void setGravityRampOn();
	void setGravityRampOff();
	SimpleObject *m_poDestinationObject;
};