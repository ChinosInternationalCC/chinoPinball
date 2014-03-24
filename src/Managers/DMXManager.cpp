//
//  DMXManager.cpp
//  chinoPinball
//
//  Created by Ovidiu on 24/03/14.
//
//

#include "DMXManager.h"

// SINGLETON initalizations
bool DMXManager::instanceFlag = false;
DMXManager* DMXManager::single = NULL;


DMXManager::DMXManager(){
    dmx.connect("tty.usbserial-EN143668"); // use the name
	//dmx.connect(0); // or use a number
    Timer = 0;
    
   dmx.setLevel(1, 100);//dimmer
}

//--------------------------------------
DMXManager* DMXManager::getInstance(void){
	if(! instanceFlag)
    {
        single = new DMXManager();
        instanceFlag = true;
        return single;
    }else{
        return single;
    }
}

void DMXManager::flashChannel(/*int channel*/void){
    int channel = 2;
    int levelMax = 100;
    
    dmx.setLevel(channel, levelMax);//color
    dmx.update();
    Timer = ofGetElapsedTimeMillis();
}

void DMXManager::update(){
    unsigned long long elapsed = ofGetElapsedTimeMillis()-Timer;
    if (
        (Timer!=0)&&
        (elapsed>500)
        ){
        
        Timer = 0;
        int channel = 2;
        int levelMin = 0;
        dmx.setLevel(channel, levelMin);
        dmx.update();
    }
}