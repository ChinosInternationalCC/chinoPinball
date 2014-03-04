//
//  ScenarioEditor.h
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 30/12/13.
//
//

#pragma once

#ifndef __ofxBulletEventsExample__ScenarioEditor__
#define __ofxBulletEventsExample__ScenarioEditor__

#include <iostream>

#endif /* defined(__ofxBulletEventsExample__ScenarioEditor__) */

#include "ofxBullet.h"
#include "Scenario.h"
#include "eventObjectScenario.h"
#include "SimpleObject.h"
#include "chinoWorld.h"

class ScenarioEditor {
    
public:
	void setup(chinoWorld &world, Scenario &scenario);
	void update();
	void draw();
    
    void keyReleased(int key);
    void onMousePick( ofxBulletMousePickEvent &e );
    
    chinoWorld *     world;
    Scenario *                scenario;
	
	bool bEscenarioEditorMode;
    void addObject(SimpleObject::shapeType type);
};