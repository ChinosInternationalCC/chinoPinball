//
//  Ball.h
//  ofxBulletEventsExample
//
//  Created by Ovidiu on 29/12/13.
//
//

#ifndef __ofxBulletEventsExample__Ball__
#define __ofxBulletEventsExample__Ball__

class Ball{
public:
    Ball(void);
    void setup(void);
    void update(void);
private:
    bool BallGameOver;
    int status; // waiting, playing, game over
};

#endif /* defined(__ofxBulletEventsExample__Ball__) */
