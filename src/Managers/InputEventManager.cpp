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
void InputEventManager::update()
{
	/*if( ofGetKeyPressed('z') ) {
		onMoveLeftLeverEvent();
	}
	if( ofGetKeyPressed('m') ) {
		onMoveRightLeverEvent();
	}*/
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
        case 'z':
        case 'Z':
            onMoveLeftLeverEvent();
			break;
        case 'm':
        case 'M':
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
            
        case 'z':
		case 'Z':
            onReleaseLeftLeverEvent();
            break;
            
        case 'm':
        case 'M':
            onReleaseRightLeverEvent();
            break;
            
    }
    
}
