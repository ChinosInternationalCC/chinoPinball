//
//  AssimpUtils.cpp
//  chinoPinball
//
//  Created by Ovidiu on 24/4/15.
//
//

#include "AssimpUtils.h"


ofVec3f AssimpUtils::getAnimatedObjectPosition(ofxAssimpModelLoader &model){
    
    ofxAssimpAnimation &animation = model.getAnimation(0);


    const aiNodeAnim * channel = animation.getAnimation()->mChannels[0];
    float progressInSeconds = animation.getPositionInSeconds();

    aiVector3D presentPosition(0, 0, 0);
    if(channel->mNumPositionKeys > 0) {
        unsigned int frame = 0;
        while(frame < channel->mNumPositionKeys - 1) {
            if(progressInSeconds < channel->mPositionKeys[frame+1].mTime) {
                break;
            }
            frame++;
        }
        
        unsigned int nextFrame = (frame + 1) % channel->mNumPositionKeys;
        const aiVectorKey & key = channel->mPositionKeys[frame];
        const aiVectorKey & nextKey = channel->mPositionKeys[nextFrame];
        double diffTime = nextKey.mTime - key.mTime;
        if(diffTime < 0.0) {
            diffTime += animation.getDurationInSeconds();
        }
        if(diffTime > 0) {
            float factor = float((progressInSeconds - key.mTime) / diffTime);
            presentPosition = key.mValue + (nextKey.mValue - key.mValue) * factor;
        } else {
            presentPosition = key.mValue;
        }
    }
/*
    cout << "Animated Pos.x " << presentPosition.x << endl;
    cout << "Animated Pos.y " << presentPosition.y << endl;
    cout << "Animated Pos.z " << presentPosition.z << endl;
 */
    return ofVec3f(presentPosition.x, presentPosition.y, presentPosition.z);
}