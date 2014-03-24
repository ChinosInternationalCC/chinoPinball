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

class DMXManager{
public:
    DMXManager();
    void flashChannel(/*int channel*/void);
    void update(void);
    static DMXManager* getInstance(void);
private:
    static bool    instanceFlag;
    static DMXManager *single;
    
    ofxDmx dmx;
    unsigned long long Timer;
};
