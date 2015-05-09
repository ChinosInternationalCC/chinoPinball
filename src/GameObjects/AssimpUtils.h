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
    /**
     *  Gets the current position of an animated object
     *
     *  @param model The model that contains the animated object
     *
     *  @return the position (x,y,z)
     */
    static ofVec3f getAnimatedObjectPosition(ofxAssimpModelLoader &model);
};