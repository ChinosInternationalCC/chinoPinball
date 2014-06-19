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
    
}

void OSCManager::listenerOnCollission(eventComunication & args){

    if(args.collision){
        ofxOscMessage m;
        m.setAddress("/Collision/Object/Id");
        m.addIntArg(args.pObject->GetObjectId());
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

#endif