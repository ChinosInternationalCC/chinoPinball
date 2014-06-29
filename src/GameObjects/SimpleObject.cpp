//
//  SimpleObject.cpp
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//

#include "SimpleObject.h"

SimpleObject::SimpleObject(SimpleMission *currentMission){
	idobject = -1;
	bAnimation = false;
    color = 0xffffff;
    highlightColor = 0xff00ff;
	scale = ofVec3f(); last_scale = scale;
	scaleXyz = 0; last_scaleXyz = scaleXyz;
    highlightTime = 60; // what units?
    this->currentMission = currentMission;
    bDebugMode = false;
	
	last_angleValX = angleValX = 0;
	last_angleValY = angleValY = 0;
	last_angleValZ = angleValZ = 0;
	
	axis2RotateX = ofVec3f(1,0,0);
	axis2RotateY = ofVec3f(0,1,0);
	axis2RotateZ = ofVec3f(0,0,1);
}

//--------------------------------------------------------------
void SimpleObject::setup(ofxBulletWorldRigid &world, ofVec3f _pos){
}

//--------------------------------------------------------------
//void SimpleObject::update(bool bEditorMode){
//}

//--------------------------------------------------------------
//void SimpleObject::draw(bool bEditorMode){
//}


void SimpleObject::SetObjectId(int objId){
    ObjectId = objId;
    
}
int SimpleObject::GetObjectId(void){
    return ObjectId;
}

void SimpleObject::setDebugMode(bool &DebugMode){
    this->bDebugMode = DebugMode;
    
}

void SimpleObject::drawDebug(void){
    
        ofSetColor(255, 255, 255);
        ofDrawBitmapString("ID:"+ofToString(GetObjectId()), position.x,position.y);
        ofDrawBitmapString("HIT:"+ofToString(currentMission->isElementHit(GetObjectId())), position.x,position.y+1);
    
}


