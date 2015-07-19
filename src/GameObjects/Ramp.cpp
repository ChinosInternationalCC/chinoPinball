//
//  Ramp.cpp
//  chinoPinball
//
//  Created by carles on 10/05/15.
//
//

#include "Ramp.h"

//--------------------------------------------------------------
Ramp::Ramp(vector <SimpleMission *> * _currentMissions) :
Obstacle(_currentMissions){
	type = ShapeTypeRamp;
}

//--------------------------------------------------------------
void Ramp::setupSpecific(){
	//TODO set special properties to this object, like dumping properties
}

//--------------------------------------------------------------
void Ramp::updateSpecific(bool bEditorMode){
	//TODO
}

//--------------------------------------------------------------
string Ramp::getObjectName(){
	return "Ramp";
}

//--------------------------------------------------------------
void Ramp::onCollisionSpecific(SimpleObject* Obj){
	//TODO active RampGravityON and then detect when the ball goes out ramp so change againg to normal gravity or return to the custom physics
}

//--------------------------------------------------------------
void Ramp::setGravityRampOn(){
	
}

//--------------------------------------------------------------
void Ramp::setGravityRampOff(){
	
}