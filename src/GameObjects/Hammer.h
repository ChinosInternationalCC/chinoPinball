//
//  Hammer.h
//  chinoPinball
//
//  Created by Ovidiu on 12/01/14.
//
//

#pragma once

#include "SimpleObject.h"

/*
 Objeto que se usa para empujar la bola (en el estado initial o para los objectos containers)

*/

class Hammer : public SimpleObject {
    
public:
    
	virtual void setup(ofxBulletWorldRigid &world, ofVec3f pos);
	virtual void update();
	virtual void draw();
	void move(float height);
    
    void onCollision();
    
	ofxBulletBox	body;
    
	float lowerLimit;
	float upperLimit;
    float speed;
    
    bool isKeyPressed;
    void onMoveEvent();
    void onReleaseEvent();
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
 /*
    energy ( float )
    Shape ( )
    ofVec3f startmov
    ofVec3f endmov
    int duration
*/
    
    /*
     setup(ofVec3f startPoint, ofVec3f EndPoint, enum Shape, ofVec3f Size, worldPos )
     start(Timer t) //
     checkDistance2ball(int idBall);

     */
    
};
