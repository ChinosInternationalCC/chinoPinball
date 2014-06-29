//
//  PinballChinoManager.h
//  chinoPinball
//
//  Created by Kuba on 28/12/13.
//
//  Description: La clase mas basica que actualiza el mundo, el estado del juego, y puede crear/tener mas de un escenario.
//

#pragma once

#include "ofMain.h"
#include "ofxBullet.h"
#include "chinoWorld.h"
#include "Scenario.h"

#include "GameStatusDisplay.h"
#include "InputEventManager.h"
#include "ofxXmlSettings.h"
#include "Ball.h"
#include "eventObjectScenario.h"
#include "eventMoveObjectScenario.h"
#include "arduComunicationManager.h"
#include "DMXManager.h"
#include "OSCManager.h"
#include "SimpleMission.h"
#include "MissionInfoDisplay.h"

#include "ScenarioEditor.h"

class PinballChinoManager: public InputEventManager {
    
public:
    
    PinballChinoManager();
    
	void setup();
	void update();
	void draw();
    void keyReleased(int key);
    void onCollision(ofxBulletCollisionData& cdata);
    
    chinoWorld     world;
	
	////Inputs
	arduComunicationManager arduCom;
    
    ///Outputs
    DMXManager dmx;
    OSCManager osc;
    
	/////////////////////////////////////////
    ofEasyCam				camera;
    ofMatrix4x4 savedPose;
	ofxXmlSettings XML;
	void saveCameraPosition(ofMatrix4x4 _camPose);
	ofMatrix4x4 loadCameraPosition();
    bool bMouseCameraEvents(bool activate);
	//////////////////////////////////////////
	ofLight					light;
    
    
    Scenario                myScenario;
    //ScenarioEditor          scenarioEditor;
    GameStatusDisplay       statusDisplay;
    MissionInfoDisplay      missionDisplay;
    
    SimpleMission *currentMission;
    bool bFullScreen;
    bool bDrawDebug;
    
    void onRestartGameEvent(void);
    void onMoveLeftLeverEvent(void);
    void onReleaseLeftLeverEvent(void);
    void onMoveRightLeverEvent(void);
    void onReleaseRightLeverEvent(void);
    void onMoveBallLauncherEvent(void);
    void onReleaseBallLauncherEvent(void);
    void ToggleDrawDebug(void);
	


    
	
private:
	
	void listenerAddObject2Scenario(eventObjectScenario & args);
	void listenerMovingObjectScenario(eventMoveObjectScenario & args);
	
};
