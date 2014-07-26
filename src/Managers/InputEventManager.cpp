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
        case 'q':
        case 'Q':
            onMoveLeftLeverEvent();
			break;
        case 'w':
        case 'W':
            onMoveRightLeverEvent();
	       break;
        case 'd':
        case 'D':
            ToggleDrawDebug();
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
            
        case 'q':
		case 'Q':
            onReleaseLeftLeverEvent();
            break;
            
        case 'w':
        case 'W':
            onReleaseRightLeverEvent();
            break;
            
    }
    
}
