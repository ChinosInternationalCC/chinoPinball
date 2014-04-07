//
//  OSCManager.cpp
//  chinoPinball
//
//  Created by Ovidiu on 07/04/14.
//
//
#ifdef USE_OSC /* configured in ExternalsConfig.h */
#include "OSCManager.h"

OSCManager::OSCManager(){
    sender.setup(HOST, PORT);
    ofAddListener(eventComunication::onNewCom,this, &OSCManager::listenerOnCollission);
    
}

void OSCManager::listenerOnCollission(eventComunication & args){
    ofxOscMessage m;
    m.setAddress("/ObjectId");
    m.addIntArg(1);
    sender.sendMessage(m);
    
}

#endif