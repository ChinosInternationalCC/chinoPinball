//
//  eventComunication.h
//  chinoPinball
//
//  Created by carles on 28/03/14.
//
//

#pragma once

#include "ofMain.h"
#include "SimpleObject.h"

class eventComunication : public ofEventArgs {
public:
	
	bool collision;
    SimpleObject *pObject;
	
    static ofEvent <eventComunication> onNewCom;
};
