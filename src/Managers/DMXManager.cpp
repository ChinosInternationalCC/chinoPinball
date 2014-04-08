//
//  DMXManager.cpp
//  chinoPinball
//
//  Created by Ovidiu on 24/03/14.
//
//

#include "DMXManager.h"


DMXManager::DMXManager(){
    if(dmx.connect("tty.usbserial-EN143668")){ // use the name
	//dmx.connect(0); // or use a number
        Timer = 0;
        dmx.setLevel(1, 100);//dimmer
        ofAddListener(eventComunication::onNewCom,this, &DMXManager::listenerOnCollission);
        DmxConnected = true;
    }
    else{
       DmxConnected = false;
    }
}



void DMXManager::flashChannel(/*int channel*/void){
    int channel = 2;
    int levelMax = 100;
    
    cout<<"DMX flash channel"<<endl;
    
    
    dmx.setLevel(channel, levelMax);//color
    dmx.update();
    Timer = ofGetElapsedTimeMillis();
}

void DMXManager::update(){
    if (DmxConnected){
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
}

void DMXManager::listenerOnCollission(eventComunication & args){
    flashChannel();
}