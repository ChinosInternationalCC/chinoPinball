//
//  eventObjectScenario.h
//  chinoPinball
//
//  Created by carles on 28/02/14.
//
//


#pragma once

#include "ofMain.h"
#include "SimpleObject.h"

class eventObjectScenario : public ofEventArgs {
public:
	
	ofVec3f	posObject;
	SimpleObject::shapeType type;
	
    static ofEvent <eventObjectScenario> onNewObject;
};
