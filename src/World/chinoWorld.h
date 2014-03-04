//
//  chinoWorld.h
//  chinoPinball
//
//  Created by Kuba on 17/02/14.
//
//

#pragma once

#include "ofxBullet.h"

class chinoWorld : public ofxBulletWorldRigid
{
    public:
        void update(void);
        ofVec3f getWorldPos();
    
};