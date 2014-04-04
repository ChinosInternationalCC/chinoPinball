//
//  DMXManager.h
//  chinoPinball
//
//  Created by Ovidiu on 24/03/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxDmx.h"
#include "eventComunication.h"

class DMXManager{
public:
    DMXManager();
    void flashChannel(/*int channel*/void);
    void update(void);
    //static DMXManager* getInstance(void);
    
    //Events
	void listenerOnCollission(eventComunication & args);
    
    
private:
    //static bool    instanceFlag;
    //static DMXManager *single;
    bool DmxConnected;
    ofxDmx dmx;
    unsigned long long Timer;
};
