//
//  eventObjectScenario.h
//  chinoPinball
//
//  Created by carles on 28/02/14.
//
//


#pragma once

#include "ofMain.h"

class eventMoveObjectScenario : public ofEventArgs {
public:
	
	bool	bMovingObject;
	
    static ofEvent <eventMoveObjectScenario> onMoveObject;
};
