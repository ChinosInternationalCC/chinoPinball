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
}

void Teleporter::SetDestinationObject(SimpleObject &object){
    m_poDestinationObject = &object;
}