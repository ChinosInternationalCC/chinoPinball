//
//  eventMission.h
//  chinoPinball
//
//  Created by Bimba on 29/06/14.
//
//

#pragma once


#include "ofMain.h"
#include "SimpleMission.h"

class eventMission : public ofEventArgs {
public:
	
    enum MissionEvent{
        MISSION_EVENT_NEW_MISSION,
        MISSION_EVENT_START_CALIFICATION,
        MISSION_EVENT_START_MISSION,
        MISSION_EVENT_END_MISSION,
        MISSION_EVENT_MISSION_COMPLETED,
        MISSION_EVENT_RESTART_MISSION
    };
    
	MissionEvent eventType;
    SimpleMission *pMission;
	//vector <SimpleMission *> * currentMissions;
	int idCurrentMission;
	
    static ofEvent <eventMission> onMissionUpdate;
};