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

class ScenarioEditor {
    
public:
	void setup(ofxBulletWorldRigid &world, Scenario &scenario);
	void update();
	void draw();
    
    void onMousePick( ofxBulletMousePickEvent &e );
    
    ofxBulletWorldRigid *     world;
    Scenario *                scenario;
};