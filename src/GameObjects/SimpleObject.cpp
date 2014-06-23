//
//  SimpleObject.cpp
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//

#include "SimpleObject.h"

SimpleObject::SimpleObject(){
	idobject = -1;
	bAnimation = false;
    color = 0xffffff;
    highlightColor = 0xff00ff;
	scale = ofVec3f(); last_scale = scale;
	scaleXyz = 0; last_scaleXyz = scaleXyz;
    highlightTime = 60; // what units?
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
