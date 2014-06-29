//
//  SimpleMission.h
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 30/12/13.
//
//

#pragma once
#include "ofMain.h"

class MissionElement{
public:
    int identifier;
    int color;
    bool hit;
};

class SimpleMission{
public:
    SimpleMission(int MissionID);
    
    
    enum enMissionStates{
        MISSION_IDLE,               // initial state
        MISSION_CALIFICATIONS,  // if one of the objects that are part of the mission is hit start tge Mission Callification
        MISSION_STARTED,        // if all the objects are hit start the mission
        MISSION_COMPLETED       // when the mission timer expires finish the mission
    };
    
    void loadMissionFromXML(int MissionID);
    enMissionStates GetMissionState(void);
    int GetCurrentMissionId(void);
    
    void OnCollision(int elementID); //onCollision should be called by the pinballChinoManager when we have
                                     //a collision and pass the element ID
    
    bool isElementPartOfMission(int elementID, int &index);
    bool isElementHit(int elementID);
    int getNoOfRemainingElements(void);
    void resetMission(void);
    void update(void); //should be called cyclic, used by the timer
    void debugDraw(void);
    int getElapsedMissionTime(void);
    int getRemainingMissionTime(void);
    
private:
    vector <MissionElement> MissionElements; //list with the IDs of the objects that are part of the mission
    int MissionID; //each Mission has a unique identifier eg. 1,2,3... configured in xml, this stores the ID of the current mission
    int MissionDuration; //each Mission has a duration configured in xml
    double Timer;
    enMissionStates MissionState;
};
