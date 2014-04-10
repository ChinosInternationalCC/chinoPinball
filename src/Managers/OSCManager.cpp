//
//  OSCManager.cpp
//  chinoPinball
//
//  Created by Ovidiu on 07/04/14.
//
//
#include "OSCManager.h"
#ifdef USE_OSC /* configured in ExternalsConfig.h */


OSCManager::OSCManager(){
    sender.setup(HOST, PORT);
    ofAddListener(eventComunication::onNewCom,this, &OSCManager::listenerOnCollission);
    
}

void OSCManager::listenerOnCollission(eventComunication & args){
    ofxOscMessage m;
    m.setAddress("/ObjectId");
    m.addIntArg(args.pObject->GetObjectId());
    sender.sendMessage(m);
    
}

#endif