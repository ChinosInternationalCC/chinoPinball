//
//  AssimpUtils.h
//  chinoPinball
//
//  Created by Ovidiu on 24/4/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class AssimpUtils{
public:
    static ofVec3f getAnimatedObjectPosition(ofxAssimpModelLoader &model);
};