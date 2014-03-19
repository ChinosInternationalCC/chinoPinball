//
//  outObjectScenario.h
//  chinoPinball
//
//  Created by Ovidiu on 12/01/14.
//
//

#ifndef __chinoPinball__outObjectScenario__
#define __chinoPinball__outObjectScenario__

#include "ofMain.h"
#include "ofxBullet.h"



/*Description: Responsable de informar que una bola se ha salido del escenrio*/

class outObjectScenario{
public:
    void setup(ofMatrix4x4 worldPosition, ofVec3f size);
    ofBoxPrimitive box;
    
    
    
    /*Vars:
     ofBox box:
     event outCallback;
     
     Functions:
     setup(ofMatrix4x4 worldPosiotion, ofVec3f size)
     loadEvent()
     */
    
};



#endif /* defined(__chinoPinball__outObjectScenario__) */
