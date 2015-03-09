//
//  WebSocketsManager.cpp
//  chinoPinball
//
//  Created by Ovidiu on 9/3/15.
//
//

#include "WebSocketsManager.h"

//--------------------------------------------------------------
void WebSocketsManager::setup(InputEventManager * inputs){
    
    this -> inputs = inputs;
    
    // setup a server with default options on port 9092
    // - pass in true after port to set up with SSL
    //bSetup = server.setup( 9093 );
    
    ofxLibwebsockets::ServerOptions options = ofxLibwebsockets::defaultServerOptions();
    options.port = 9092;
	options.bUseSSL = false; // you'll have to manually accept this self-signed cert if 'true'!
    bSetup = server.setup( options );
    
    // this adds your app as a listener for the server
    server.addListener(this);
    

    /* open browser for tests, in the end this should be deleted */
    string url = "http";
    if ( server.usingSSL() ){
        url += "s";
    }
    url += "://localhost:" + ofToString( server.getPort() );
    ofLaunchBrowser(url);
}

//--------------------------------------------------------------
void WebSocketsManager::onConnect( ofxLibwebsockets::Event& args ){
    cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void WebSocketsManager::onOpen( ofxLibwebsockets::Event& args ){
    cout<<"new connection open"<<endl;
    messages.push_back("New connection from " + args.conn.getClientIP() + ", " + args.conn.getClientName() );
}

//--------------------------------------------------------------
void WebSocketsManager::onClose( ofxLibwebsockets::Event& args ){
    cout<<"on close"<<endl;
    messages.push_back("Connection closed");
}

//--------------------------------------------------------------
void WebSocketsManager::onIdle( ofxLibwebsockets::Event& args ){
    cout<<"on idle"<<endl;
}

//--------------------------------------------------------------
void WebSocketsManager::onMessage( ofxLibwebsockets::Event& args ){
    cout<<"got message "<<args.message<<endl;
    
    if (args.message.compare("left") == 0){
        this->inputs->onMoveLeftLeverEvent();
    }
    
    if (args.message.compare("right") == 0){
        this->inputs->onMoveRightLeverEvent();
    }
    
    if (args.message.compare("left_") == 0){
        this->inputs->onReleaseLeftLeverEvent();
    }
    
    if (args.message.compare("right_") == 0){
        this->inputs->onReleaseRightLeverEvent();
    }
    
    
    // trace out string messages or JSON messages!
    if ( !args.json.isNull() ){
        messages.push_back("New message: " + args.json.toStyledString() + " from " + args.conn.getClientName() );
    } else {
        messages.push_back("New message: " + args.message + " from " + args.conn.getClientName() );
    }
    
    // echo server = send message right back!
    args.conn.send( args.message );
}

//--------------------------------------------------------------
void WebSocketsManager::onBroadcast( ofxLibwebsockets::Event& args ){
    cout<<"got broadcast "<<args.message<<endl;
}
