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


class Ball : ofxBulletSphere{
public:
    Ball(void);
    void setup(ofxBulletWorldRigid &world);
    void update(void);
    void drawBall(void);
    bool isInsideScenario(ofBoxPrimitive box);
    bool setGameOverBall(void); //callback from GameOverCollision,
                                //returns true if the status was changed, false if already set
    
    enum BallStatus{
        BallStatusWaiting = 0,
        BallStatusPlaying,
        BallStatusGameOver
    };

private:
    BallStatus m_status; // waiting, playing, game over
   // ofxBulletSphere *BulletBallShape; // generic bullet shape object
};

#endif /* defined(__ofxBulletEventsExample__Ball__) */
