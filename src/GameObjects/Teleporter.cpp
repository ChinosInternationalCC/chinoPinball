//
//  Teleporter.cpp
//  chinoPinball
//
//  Created by Ovidiu on 9/5/15.
//
//

#include "Teleporter.h"

Teleporter::Teleporter(vector <SimpleMission *> * _currentMissions)
: Obstacle(_currentMissions){
    m_poDestinationObject = NULL;
}

void Teleporter::setupSpecific(){
    type = ShapeTypeTeleporter;
}

void Teleporter::updateSpecific(bool bEditorMode){
    //TODO
}

string Teleporter::getObjectName(){
    return "Teleporter";
}

void Teleporter::onCollisionSpecific(){
    //TODO move the ball to the destination point m_poDestinationObject
    
    if (bSticky){
        //if the sticky flag is active the ball should remain stuck
    }
}

void Teleporter::ReleaseBall(){
    if (bBallStuck){
        //TODO release the Ball
    }
}

void Teleporter::SetDestinationObject(SimpleObject &object){
    m_poDestinationObject = &object;
}

void Teleporter::SetMultiBallStickyFlag(bool bFlag){
    bSticky = bFlag;
    if (bFlag){
        m_poDestinationObject = this;
    }
}

bool Teleporter::GetMultiBallStickyFlag(void){
    return bSticky;
}

bool Teleporter::IsBallStuck(){
    return bBallStuck;
}