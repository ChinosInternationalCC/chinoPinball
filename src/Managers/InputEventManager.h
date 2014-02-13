//
//  InputEventManager.h
//  chinoPinball
//
//  Created by Ovidiu on 06/02/14.
//
//

#ifndef __chinoPinball__InputEventManager__
#define __chinoPinball__InputEventManager__

#include "ofMain.h"
#include "ofxOsc.h"

/* this class is the entry point from all the interfaces suported
 * eg: keyboard, OSC TBD
 * should be extended by the PinballChino manager
 * PinbalChinoManager should implement the pure virtual methods
 */
class InputEventManager: public ofxOscReceiver
{
public:
    InputEventManager();
    
    virtual void onMoveLeftLeverEvent(void) = 0;
    virtual void onMoveRightLeverEvent(void) = 0;
    virtual void onMoveBallLauncherEvent(void) = 0;
    virtual void onRestartGameEvent(void) = 0;
    

    
    
};


#endif /* defined(__chinoPinball__InputEventManager__) */
