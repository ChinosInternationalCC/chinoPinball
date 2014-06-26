//
//  SimpleMission.cpp
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 30/12/13.
//
//

#include "SimpleMission.h"
#include "ofxXmlSettings.h"

SimpleMission::SimpleMission(int MissionID){
    loadMissionFromXML(MissionID);
    
}

//------------------------------------------------
void SimpleMission::loadMissionFromXML(int MissionID){
    ofxXmlSettings MissionXml;
    cout<<"Load mission from xml"<<endl;
    if(MissionXml.loadFile("missions.xml")){
        
        MissionXml.pushTag("missions");
        
        int numberOfSavedObjects = MissionXml.getNumTags("mission");
        cout<<ofToString(numberOfSavedObjects)<<endl;
        for(int i = 0; i < numberOfSavedObjects; i++){
            
            MissionXml.pushTag("mission", i);
            if (MissionID == MissionXml.getValue("missionID", 0)){
                this->MissionID = MissionID;
                MissionDuration = MissionXml.getValue("duration", 0);
                int numberOfObjects = MissionXml.getNumTags("ID");
                for(int i = 0; i < numberOfObjects; i++){
                MissionXml.pushTag("mission", i);
                    cout<< ofToString(MissionXml.getValue("duration", 0))<<endl;
                MissionXml.popTag();
                }
            }

            MissionXml.popTag();
        }//for mission
        
        MissionXml.popTag();
    }
    
    else{
        
        ofLogError("Mission file did not load!");
        
    }

    MissionState = MISSION_IDLE;
}

//------------------------------------------------
SimpleMission::enMissionStates SimpleMission::GetMissionState(void){
    return MissionState;
    
}

//------------------------------------------------
int SimpleMission::GetCurrentMissionId(void){
    return MissionID;
}

//------------------------------------------------
void SimpleMission::OnCollision(int elementID){
    //if (elementID) in MissionElements
    //  MissionElements.pop_back();
    // MissionState = MISSION_CALIFICATIONS;
    
    
}