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
private:
    
    ofLight pointLight;
    float radius;
	ofVec3f center;
};