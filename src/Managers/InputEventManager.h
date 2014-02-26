//
//  InputEventManager.h
//  chinoPinball
//
//  Created by Ovidiu on 06/02/14.
//
//

#ifndef __chinoPinball__InputEventManager__
#define __chinoPinball__InputEventManager__


#include "ExternalsConfig.h"
#include "ofMain.h"
#ifdef USE_OSC /* configured in ExternalsConfig.h */
#include "ofxOsc.h"
#endif

/* this class is the entry point from all the interfaces suported
 * eg: keyboard, OSC TBD
 * should be extended by the PinballChino manager
 * PinbalChinoManager should implement the pure virtual methods
 */
class InputEventManager
{
public:
    InputEventManager();
    
    virtual void onMoveLeftLeverEvent(void) = 0;
    virtual void onMoveRightLeverEvent(void) = 0;
    virtual void onMoveBallLauncherEvent(void) = 0;
    virtual void onRestartGameEvent(void) = 0;
    
#ifdef USE_OSC
    ofxOscReceiver oscReceiver;
#endif
    
    void keyPressed(int key);
    void keyReleased(int key);
    
};


#endif /* defined(__chinoPinball__InputEventManager__) */
