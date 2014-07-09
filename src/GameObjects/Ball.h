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
    Ball(vector <SimpleMission *> * _currentMissions);//SimpleObjects force that
    Ball(SimpleObject simpleObject);
    void setup(ofxBulletWorldRigid &world, ofVec3f pos);
    void update(bool bEditorMode);
    void draw(bool bEditorMode);

	void setupRot();
    
    float radius;
    float mass;
    ofxBulletSphere body;
    ofxBulletWorldRigid world;
    
    bool isInsideBox(float boxSize);
    bool setGameOverBall(void); //callback from GameOverCollision,
                                //returns true if the status was changed, false if already set
    enum BallStatus{
        BallStatusWaiting = 0,
        BallStatusPlaying,
        BallStatusGameOver
    };
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void reset();
    
    void onCollision();
    void setDefaultZ();
    void setPosition(ofVec3f position);
    		void setRotation(ofQuaternion rotation);

private:
    BallStatus m_status; // waiting, playing, game over
	
	
	//shadow fake
	ofCylinderPrimitive shadow;
    
};

#endif /* defined(__ofxBulletEventsExample__Ball__) */
