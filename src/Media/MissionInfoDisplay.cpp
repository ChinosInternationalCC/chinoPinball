//
//  MissionInfoDisplay.cpp
//  chinoPinball
//
//  Created by Bimba on 29/06/14.
//
//

#include "MissionInfoDisplay.h"

MissionInfoDisplay::MissionInfoDisplay(void){
    currentMission = NULL;
    str = "";
    // The third parameter is depth, use it to extrude the shape.
    font.loadFont("ARCADE.TTF", 200);
    startPositionX = 200;
    startPositionY = 200;
    
    ofAddListener(eventMission::onMissionUpdate,this, &MissionInfoDisplay::listenerOnUpdateMission);
}

void MissionInfoDisplay::draw(void){
    if (currentMission != NULL){
    
        
    
        switch(currentMissionState){
            case SimpleMission::MISSION_IDLE:
           
                break;
            case SimpleMission::MISSION_CALIFICATIONS:
           
                break;
            case SimpleMission::MISSION_STARTED:
                drawElapsedMissionTime();
            
                       break;
            case SimpleMission::MISSION_COMPLETED:
        
                break;
            
        }
    }
    

    
}

void MissionInfoDisplay::listenerOnUpdateMission(eventMission & args){
    
    currentMission = args.pMission;
    currentMissionState = args.pMission->GetMissionState();
    
    switch(args.eventType){
        case eventMission::MISSION_EVENT_START_MISSION:

            break;
        case eventMission::MISSION_EVENT_END_MISSION:

            
            break;
        case eventMission::MISSION_EVENT_MISSION_COMPLETED:

            
            break;
        case eventMission::MISSION_EVENT_START_CALIFICATION:

            
            break;
        case eventMission::MISSION_EVENT_RESTART_MISSION:

            
            break;
        case eventMission::MISSION_EVENT_NEW_MISSION:

            
            break;
            
    }
}

void MissionInfoDisplay::drawElapsedMissionTime(void){
    cam.begin();
    MediaUtils::billboardBegin();//always facing the camera
    {
        ofScale(1, -1, 1);  // Flip back since we're in 3D.
        //font.drawString(str, font.stringWidth(str) * -0.5f, font.stringHeight(str) * 0.5f);
        ofSetColor(5, 200, 220);
        font.drawString(str+"  "+ofToString(currentMission->getElapsedMissionTime(), 2), -500, 0);
        
        
    }
    MediaUtils::billboardEnd();
    cam.end();
    

    
}
