//
//  InputEventManager.cpp
//  chinoPinball
//
//  Created by Ovidiu on 06/02/14.
//
//

#include "InputEventManager.h"


InputEventManager::InputEventManager(){
    
}

//--------------------------------------------------------------
void InputEventManager::keyPressed(int key)
{
    
    switch(key)
    {
        case OF_KEY_RETURN:
            onRestartGameEvent();
            break;
            
        case OF_KEY_DOWN:
            onMoveBallLauncherEvent();
            break;
            
        case OF_KEY_LEFT_SHIFT:
            onMoveLeftLeverEvent();
            break;
            
        case OF_KEY_RIGHT_SHIFT:
            onMoveRightLeverEvent();
            break;
            
    }
    
}

//--------------------------------------------------------------
void InputEventManager::keyReleased(int key)
{
    
    switch(key)
    {
            
        case OF_KEY_DOWN:
            onReleaseBallLauncherEvent();
            break;
            
        case OF_KEY_LEFT_SHIFT:
            onReleaseLeftLeverEvent();
            break;
            
        case OF_KEY_RIGHT_SHIFT:
            onReleaseRightLeverEvent();
            break;
            
    }
    
}
