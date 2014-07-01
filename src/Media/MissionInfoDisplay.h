//
//  MissionInfoDisplay.h
//  chinoPinball
//
//  Created by Bimba on 29/06/14.
//
//

#pragma once

#include "SimpleMission.h"
#include "eventMission.h"
#include "ofxFTGL.h"
#include "MediaUtils.h"

class MissionInfoDisplay{
public:
    MissionInfoDisplay(void);
    void draw(void);
    
    void listenerOnUpdateMission(eventMission & args);
    
private:
	SimpleMission *currentMission;
	//vector <SimpleMission *> * _currentMissions;
	int currentMissionId;
	
    SimpleMission::enMissionStates currentMissionState;
    ofxFTGLFont fontLarge, fontMedium;
    string str;
    ofLight light;
    ofMaterial material;
    int startPositionX, startPositionY;
    ofEasyCam cam;
    
    int SplashScreenDuration;
    double SplashScreenTimer;
    
    
    void drawElapsedMissionTime(void);
};
