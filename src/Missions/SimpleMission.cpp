
//
//  SimpleMission.cpp
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 30/12/13.
//
//

#include "SimpleMission.h"
#include "ofxXmlSettings.h"
#include "eventMission.h"

SimpleMission::SimpleMission(int MissionID){
    loadMissionFromXML(MissionID);
    
    
    eventMission evtMission;
    evtMission.idCurrentMission = MissionID;
	//evtMission.currentMissions = this; //TODO solve how to copy this..
	
    evtMission.eventType = eventMission::MISSION_EVENT_NEW_MISSION;
    ofNotifyEvent(eventMission::onMissionUpdate, evtMission);
    
	MissionID = 0;
}

//------------------------------------------------
void SimpleMission::loadMissionFromXML(int MissionID){
    ofxXmlSettings MissionXml;
    cout<<"Load mission from xml"<<endl;
    if(MissionXml.loadFile("missions.xml")){
        
        MissionXml.pushTag("missions");
        
        int numberOfSavedObjects = MissionXml.getNumTags("mission");
        for(int i = 0; i < numberOfSavedObjects; i++){
            
            MissionXml.pushTag("mission", i);
            if (MissionID == MissionXml.getValue("missionID", 0)){
                this->MissionID = MissionID;
                MissionDuration = MissionXml.getValue("duration", 0);
                int numberOfObjects = MissionXml.getNumTags("object");
                for(int j = 0; j < numberOfObjects; j++){
                MissionXml.pushTag("object", j);
                    MissionElement element;
                    //cout<< ofToString(MissionXml.getValue("id", 0))<<endl;
                    element.identifier = MissionXml.getValue("id", 0);
                    element.color = MissionXml.getValue("color", 0);
                    element.hit = false;
                    MissionElements.push_back(element);
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

void SimpleMission::debugDraw(void){
    int posX = 100;
    int posY = ofGetHeight()-100;
    ofSetColor(255, 255, 255);
    string tmp;
    switch(MissionState){
        case MISSION_IDLE:
            tmp = "MISSION_IDLE";
            break;
        case MISSION_CALIFICATIONS:
            tmp = "MISSION_CALIFICATIONS";
            break;
        case MISSION_STARTED:
            tmp = "MISSION_STARTED";
            break;
        case MISSION_COMPLETED:
            tmp = "MISSION_COMPLETED";
            break;
            
    }

    ofDrawBitmapString(tmp, posX,posY);

    ofDrawBitmapString("Id mission:", posX,posY-20);
	ofDrawBitmapString(ofToString(MissionID, 0), posX + 100,posY-20);
	
    ofDrawBitmapString("Mission Elements:", posX,posY);
	
    ofDrawBitmapString("HIT", posX,posY+40);
    int NoOfElements = MissionElements.size();
    for (int i=0; i < NoOfElements; i++){
        ofDrawBitmapString(ofToString(MissionElements[i].identifier),posX+150+(20*i), posY+20);
        if (true == MissionElements[i].hit){
            ofDrawBitmapString(ofToString(MissionElements[i].identifier),posX+150+(20*i), posY+20);
        }
    }
    if (MISSION_STARTED == MissionState)
        ofDrawBitmapString("Elapsed Milis"+ofToString(ofGetElapsedTimeMillis()-Timer),posX, posY+40);
}

//------------------------------------------------
void SimpleMission::OnCollision(int elementID){
    int i;
    eventMission evtMission;
    
	evtMission.pMission = this;
	evtMission.idCurrentMission = MissionID;
    
	
	
    switch(MissionState){
        case MISSION_IDLE:
            if (isElementPartOfMission(elementID,i)){
                MissionElements[i].hit = true;
                MissionState = MISSION_CALIFICATIONS;
                
                /* notify the state change */
                evtMission.eventType = eventMission::MISSION_EVENT_START_CALIFICATION;
                ofNotifyEvent(eventMission::onMissionUpdate, evtMission);
            }
            break;
        case MISSION_CALIFICATIONS:
            if (isElementPartOfMission(elementID,i)){
                MissionElements[i].hit = true;
                if (0 == getNoOfRemainingElements()){
                    MissionState = MISSION_STARTED;
                    
                    /* notify the state change */
                    evtMission.eventType = eventMission::MISSION_EVENT_START_MISSION;
                    ofNotifyEvent(eventMission::onMissionUpdate, evtMission);
                    
                    //start the mission timer
                    Timer = ofGetElapsedTimeMillis();
                }
                
            }
            
            break;
        case MISSION_STARTED:

            break;
        case MISSION_COMPLETED:

            break;
     
    }

    
    
}

//------------------------------------------------
void SimpleMission::update(void){
    if (MissionState == MISSION_STARTED){
        /* the timer is checked only in the MISSION_STARTED state */
        if ((ofGetElapsedTimeMillis() - Timer) > MissionDuration){     /// TODO SET idcurrentMission to 0 when this finish the timer
            MissionState = MISSION_COMPLETED;
            /* Notify the state change */
            
            eventMission evtMission;
            
			evtMission.pMission = this;//TODO
			evtMission.idCurrentMission = MissionID;
			
            evtMission.eventType = eventMission::MISSION_EVENT_MISSION_COMPLETED;
            ofNotifyEvent(eventMission::onMissionUpdate, evtMission);

            
        }
    }
    if (MissionState == MISSION_COMPLETED){
        resetMission();
    }
    
}

//------------------------------------------------
bool SimpleMission::isElementPartOfMission(int elementID, int &index){
    bool bResult = false;
    int NoOfElements = MissionElements.size();
    for (int i=0; i < NoOfElements; i++){
        if (elementID == MissionElements[i].identifier){
            index = i;
            bResult = true;
        }
    }
    return bResult;
}

//------------------------------------------------
int SimpleMission::getNoOfRemainingElements(void){
    int count = 0;
    int NoOfElements = MissionElements.size();
    for (int i=0; i < NoOfElements; i++){
        if (false == MissionElements[i].hit)
            count++;
    }
    return count;
}

//------------------------------------------------
void SimpleMission::resetMission(void){
    int NoOfElements = MissionElements.size();
    for (int i=0; i < NoOfElements; i++){
        MissionElements[i].hit = false;
    }
    MissionState = MISSION_IDLE;
    
    eventMission evtMission;
    
	evtMission.pMission = this; //TODO
	evtMission.idCurrentMission = MissionID;
	
    evtMission.eventType = eventMission::MISSION_EVENT_RESTART_MISSION;
    ofNotifyEvent(eventMission::onMissionUpdate, evtMission);

    
    
}

//------------------------------------------------
bool SimpleMission::isElementHit(int elementID){
    int NoOfElements = MissionElements.size();
    for (int i=0; i < NoOfElements; i++){
        if ((elementID == MissionElements[i].identifier)&&
            (true == MissionElements[i].hit))
        return true;
    }
    return false;
}

int SimpleMission::getElapsedMissionTime(void){
    int elapsedTime = -1;
    if (MISSION_STARTED == MissionState)
        elapsedTime = ofGetElapsedTimeMillis()-Timer;
    return elapsedTime;
}

int SimpleMission::getRemainingMissionTime(void){
    int elapsedTime = -1;
    if (MISSION_STARTED == MissionState)
        elapsedTime = MissionDuration + (Timer - ofGetElapsedTimeMillis());
    return elapsedTime;
    
}

