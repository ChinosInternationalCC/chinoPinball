//
//  Gravity.cpp
//  chinoPinball
//
//  Created by Ovidiu on 9/5/15.
//
//

#include "Gravity.h"

Gravity::Gravity(vector <SimpleMission *> * _currentMissions)
: Obstacle(_currentMissions){
}
void Gravity::setupSpecific(){
    type = ShapeTypeGravity;
}

void Gravity::updateSpecific(bool bEditorMode){
    /* set the world gravity to the position of this object */
    m_poWorld->setGravity(this->position);
}

string Gravity::getObjectName(){
    return "Gravity";
}
