//
//  FreeTransformObject.h
//  chinoPinball
//
//  Created by Ovidiu on 7/6/15.
//
//

#pragma once

#include "ofMain.h"

class SimpleObject;

class FreeTransformObject{
public:
    FreeTransformObject(SimpleObject *pSimpleObj);
    void update();
    
    void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);
    void SetLastRotation(ofQuaternion rotation);
    void SetLastScale(ofVec3f scale);
    void autoScalingXYZ();
    
    float		angleValX;
	float		angleValY;
	float		angleValZ;
    
    float scaleXyz;
private:
    SimpleObject *m_poSimpleObj;
    
    //Rotations
	ofQuaternion    last_rotation;
	ofVec3f		axis2RotateX;
	ofVec3f		axis2RotateY;
	ofVec3f		axis2RotateZ;
	float       last_angleValX;
	float		last_angleValY;
	float		last_angleValZ;
    
    float last_positionX, last_positionY, last_positionZ;
    
    ofVec3f last_scale;  // if we load a 3D model this variable should store the scale factors
	float last_scaleXyz;
    // with the correct values so that our model nicely fits inside the Scenario
};