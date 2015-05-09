//
//  OSCManager.h
//  chinoPinball
//
//  Created by Ovidiu on 07/04/14.
//
//

#pragma once
#include "ExternalsConfig.h"

#ifdef USE_OSC /* configured in ExternalsConfig.h */

#include "ofMain.h"
#include "ofxOsc.h"
#include "eventComunication.h"
#include "eventMission.h"
#include "InputEventManager.h"

#define HOST "localhost"
#define PORT 9001
#define RECEIVER_PORT 9002

class OSCManager{
	
	
	
public:
    OSCManager();
    
    //Events
	void listenerOnCollission(eventComunication & args);
    void listenerOnUpdateMission(eventMission & args);
    
    void update(InputEventManager * inputs);
    
private:
    
    ofxOscSender sender;
    ofxOscReceiver receiver;
};


#endif