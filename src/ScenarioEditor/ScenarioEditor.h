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
#include "eventMoveObjectScenario.h"
#include "SimpleObject.h"
#include "chinoWorld.h"

class ScenarioEditor {
    
public:
	void setup(chinoWorld &world, Scenario &scenario);
	void update();
	void draw();
    
    void keyReleased(int key);
    void onMousePick( ofxBulletMousePickEvent &e );
	//ofVec3f objPressedLoc;
	ofVec2f mousePickLoc;
    
    chinoWorld *	world;
    Scenario *		scenario;
	
	bool bEscenarioEditorMode;
    
    SimpleObject *	selectedObject; /* current selected object, NULL if no object selected */
   
	void mouseDragged(ofMouseEventArgs &args);
    void mouseMoved(ofMouseEventArgs &args);
    void mousePressed(ofMouseEventArgs &args);
    void mouseReleased(ofMouseEventArgs &args);
    
    void addObject(SimpleObject::shapeType type);
    
    ofMouseEventArgs mouseOldPosition;
	
	
};