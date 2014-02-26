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
    }
    
}

//--------------------------------------------------------------
void InputEventManager::keyReleased(int key)
{
    
    switch(key)
    {
            
    }
    
}
