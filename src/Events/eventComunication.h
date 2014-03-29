//
//  eventComunication.h
//  chinoPinball
//
//  Created by carles on 28/03/14.
//
//

#pragma once

#include "ofMain.h"

class eventComunication : public ofEventArgs {
public:
	
	bool collision;
	
    static ofEvent <eventComunication> onNewCom;
};
