//
//  OSCManager.h
//  chinoPinball
//
//  Created by Ovidiu on 07/04/14.
//
//

#pragma once
#ifdef USE_OSC /* configured in ExternalsConfig.h */

#include "ofMain.h"
#include "ofxOsc.h"
#include "eventComunication.h"

#define HOST "localhost"
#define PORT 12345

class OSCManager{
public:
    OSCManager();
    
    //Events
	void listenerOnCollission(eventComunication & args);
    
    
private:
    
    ofxOscSender sender;
};


#endif