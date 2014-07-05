//
//  OSCManager.cpp
//  chinoPinball
//
//  Created by Ovidiu on 07/04/14.
//
//
#include "OSCManager.h"
#ifdef USE_OSC /* configured in ExternalsConfig.h */
#include "GameStatus.h"

OSCManager::OSCManager(){
    sender.setup(HOST, PORT);
    ofAddListener(eventComunication::onNewCom,this, &OSCManager::listenerOnCollission);
    ofAddListener(eventMission::onMissionUpdate,this, &OSCManager::listenerOnUpdateMission);
    
}

void OSCManager::listenerOnCollission(eventComunication & args){

    if(args.collision){
        ofxOscMessage m;
        m.setAddress("/Collision/Object/Id");
        m.addIntArg(args.pObject->GetObjectId());
        sender.sendMessage(m);
		
		m.clear();
        m.setAddress("/Collision/Object/"+ofToString(args.pObject->GetObjectId()));
        m.addFloatArg(1.0);
        sender.sendMessage(m);
		
		m.clear();
        m.setAddress("/Collision/Object/"+ofToString(args.pObject->GetObjectId()));
        m.addFloatArg(0.0);
        sender.sendMessage(m);
    
        m.clear();
        m.setAddress("/Collision/Object/Name");
        m.addStringArg(args.pObject->getObjectName());
        sender.sendMessage(m);
    
        m.clear();
        m.setAddress("/Collision/Object/Position");
        m.addFloatArg(args.pObject->position.x);
        m.addFloatArg(args.pObject->position.y);
        m.addFloatArg(args.pObject->position.z);
        sender.sendMessage(m);
        
        /* send also the score on a collision */
        m.clear();
        m.setAddress("/Score");
        
        GameStatus *status;
        status = GameStatus::getInstance();
        
        m.addIntArg(status->GetCurrentPlayerScore());
        sender.sendMessage(m);
    }
    
}

void OSCManager::listenerOnUpdateMission(eventMission & args){
    ofxOscMessage m;
    
    switch(args.eventType){
        case eventMission::MISSION_EVENT_START_MISSION:
            m.setAddress("/Mission/Event");
            m.addIntArg(args.eventType);
            sender.sendMessage(m);
            m.clear();
            
            if (NULL != args.pMission){
                m.setAddress("/Mission/ID");
                m.addIntArg(args.pMission->GetCurrentMissionId());
                sender.sendMessage(m);
            }
            
            break;
        case eventMission::MISSION_EVENT_END_MISSION:
            m.setAddress("/Mission/Event");
            m.addIntArg(args.eventType);
            sender.sendMessage(m);
            m.clear();
            
            if (NULL != args.pMission){
                m.setAddress("/Mission/ID");
                m.addIntArg(args.pMission->GetCurrentMissionId());
                sender.sendMessage(m);
            }
            break;
        case eventMission::MISSION_EVENT_MISSION_COMPLETED:
            m.setAddress("/Mission/Event");
            m.addIntArg(args.eventType);
            sender.sendMessage(m);
            m.clear();
            
            break;
        case eventMission::MISSION_EVENT_START_CALIFICATION:
            m.setAddress("/Mission/Event");
            m.addIntArg(args.eventType);
            sender.sendMessage(m);
            m.clear();
            
            break;
        case eventMission::MISSION_EVENT_RESTART_MISSION:
            m.setAddress("/Mission/Event");
            m.addIntArg(args.eventType);
            sender.sendMessage(m);
            m.clear();
            
            break;
        case eventMission::MISSION_EVENT_NEW_MISSION:
            m.setAddress("/Mission/Event");
            m.addIntArg(args.eventType);
            sender.sendMessage(m);
            m.clear();
            
            break;
            
    }
}

#endif