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


class Ball : public ofxBulletSphere{
public:
    Ball(void);
    void setup(ofxBulletWorldRigid &world, ofVec3f position);
    void update(void);
    void draw(void);
    
    ofVec3f startPosition;
    float radius = .3;
    float mass = 2;
    
    ofxBulletWorldRigid world;
    
	void keyPressed(ofKeyEventArgs& key);
	void keyReleased(ofKeyEventArgs& key);
    
    bool isInsideScenario(ofBoxPrimitive box);
    bool setGameOverBall(void); //callback from GameOverCollision,
                                //returns true if the status was changed, false if already set
    enum BallStatus{
        BallStatusWaiting = 0,
        BallStatusPlaying,
        BallStatusGameOver
    };
    
    void reset();

private:
    BallStatus m_status; // waiting, playing, game over
   // ofxBulletSphere *BulletBallShape; // generic bullet shape object
    
};

#endif /* defined(__ofxBulletEventsExample__Ball__) */
