//
//  LightsManager.h
//  chinoPinball
//
//  Created by Bimba on 29/06/14.
//
//

#pragma once
#include "ofMain.h"

class LightsManager{
public:
    void setup(void);
    void update(void);
    void enable(void);
    void disable(void);
    void draw(void);
    void setMainLightPosition(ofVec3f lightPos);
private:
    
    //ofLight pointLight,
	ofLight mainLight;
    float radius;
	ofVec3f center;
    ofVec3f mainLightPosition;
};