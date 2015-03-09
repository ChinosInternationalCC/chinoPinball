//
//  WebSocketsManager.h
//  chinoPinball
//
//  Created by Ovidiu on 9/3/15.
//
//

#pragma once

#include "ofxLibwebsockets.h"
#include "InputEventManager.h"

#define NUM_MESSAGES 30 // how many past messages we want to keep

class WebSocketsManager{
public:
    void setup(InputEventManager *inputs);
    
    InputEventManager * inputs;
    ofxLibwebsockets::Server server;
    
    bool bSetup;
    
    //queue of rec'd messages
    vector<string> messages;
    
    //string to send to clients
    string toSend;
    
    // websocket methods
    void onConnect( ofxLibwebsockets::Event& args );
    void onOpen( ofxLibwebsockets::Event& args );
    void onClose( ofxLibwebsockets::Event& args );
    void onIdle( ofxLibwebsockets::Event& args );
    void onMessage( ofxLibwebsockets::Event& args );
    void onBroadcast( ofxLibwebsockets::Event& args );
};