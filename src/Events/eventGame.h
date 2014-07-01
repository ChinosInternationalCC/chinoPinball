//
//  eventGame.h
//  chinoPinball
//
//  Created by carles on 01/07/14.
//
//

#pragma once

#include "ofMain.h"

class eventGame : public ofEventArgs {
public:
	
    enum GameEvent{
        GAME_EVENT_HAMMER_LAUNCH
    };
    
	GameEvent gameEvent;
	
    static ofEvent <eventGame> onGameEvent;
};



