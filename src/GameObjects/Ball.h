//
//  Ball.h
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 29/12/13.
//
//

#ifndef __ofxBulletEventsExample__Ball__
#define __ofxBulletEventsExample__Ball__

#include "ofMain.h"
#include "ofxBullet.h"
#include "SimpleObject.h"
#include "SoundManager.h"


class Ball : public SimpleObject
{
public:
    Ball(vector <SimpleMission *> * _currentMissions, float radius);//SimpleObjects force that
    void setup(ofxBulletWorldRigid &myWorld,
               ofVec3f pos,
               float mass,
               float radius,
               float restitution,
               float friction);
    
    void update(bool bEditorMode);
    void updateSpecific(bool bEditorMode);
    void draw(bool bEditorMode);

	void setupRot();
    
    float radius;

    ofxBulletSphere body;

    
    bool isInsideBox(float boxSize);

    enum BallStatus{
        BallStatusWaiting = 0,
        BallStatusPlaying,
        BallStatusGameOver
    };
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void reset();
    
    void onCollision();
    
    ofVec3f getInitialPos();

private:

	ofVec3f m_initialPos;
	
	//shadow fake
	ofCylinderPrimitive shadow;
    
};

#endif /* defined(__ofxBulletEventsExample__Ball__) */
