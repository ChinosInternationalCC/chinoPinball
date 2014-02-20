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

class PinballChinoManager: public InputEventManager {
    
public:
    
    PinballChinoManager();
    
	void setup();
	void update();
	void draw();
    
    chinoWorld     world;

//	ofCamera                camera;
    ofEasyCam				camera;
	ofLight					light;
    
    Scenario                myScenario;
    ScenarioEditor          scenarioEditor;
    GameStatusDisplay       statusDisplay;
    
    void onRestartGameEvent(void);
    void onMoveLeftLeverEvent(void);
    void onMoveRightLeverEvent(void);
    void onMoveBallLauncherEvent(void);

    
};
