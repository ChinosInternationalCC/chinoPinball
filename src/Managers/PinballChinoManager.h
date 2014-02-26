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
#include "Scenario.h"
#include "ScenarioEditor.h"
#include "GameStatusDisplay.h"
#include "InputEventManager.h"
#include "chinoWorld.h"
#include "ofxXmlSettings.h"
#include "ofxGrabCam.h"
#include "Ball.h"

class PinballChinoManager: public InputEventManager {
    
public:
    
    PinballChinoManager();
    
	void setup();
	void update();
	void draw();
    void keyReleased(int key);
    void onCollision(ofxBulletCollisionData& cdata);
    
    chinoWorld     world;

    //	ofCamera                camera;
    ofEasyCam				camera;
    //////////////////////////////////////////
	//camera settings
//	ofxGrabCam camera;
	ofMatrix4x4 savedPose;
    
	ofxXmlSettings XML;
	void saveCameraPosition(ofMatrix4x4 _camPose);
	ofMatrix4x4 loadCameraPosition();
    //////////////////////////////////////////
    
	ofLight					light;
    
    Scenario                myScenario;
    ScenarioEditor          scenarioEditor;
    GameStatusDisplay       statusDisplay;
    bool bFullScreen;
    
    void onRestartGameEvent(void);
    void onMoveLeftLeverEvent(void);
    void onMoveRightLeverEvent(void);
    void onMoveBallLauncherEvent(void);

    
};
