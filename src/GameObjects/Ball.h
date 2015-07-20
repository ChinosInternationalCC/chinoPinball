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

class BallAttrib : public SimpleObjectAttrib{
public:
    inline BallAttrib(string modelPath,
					  ofVec3f _position,
                      float _damping,
                      float _friction,
                      float _mass,
                      float _restitution,
                      float _radius,
					  ofVec3f _ModelScale);
    float radius;
    
};

inline BallAttrib::BallAttrib(string _modelPath,
							  ofVec3f _position,
                              float _damping,
                              float _friction,
                              float _mass,
                              float _restitution,
                              float _radius,
							  ofVec3f _ModelScale) :
    SimpleObjectAttrib(_modelPath,
					   _position,
					   _damping,
					   _friction,
					   _mass,
					   _restitution,
					   _ModelScale)
	{
        radius = _radius;
	}


class Ball : public SimpleObject
{
public:
	
	enum BallState{
		BALL_STATE_INIT,
		BALL_STATE_ROLLING,
		BALL_STATE_STUCK
	};
	
    Ball(vector <SimpleMission *> * _currentMissions, float radius);//SimpleObjects force that
    ~Ball();
    void setup(ofxBulletWorldRigid &myWorld,
               SimpleObjectAttrib *Attrib
               /*
               ofVec3f pos,
               float mass,
               float radius,
               float restitution,
               float friction
                */);
    
    void updateSpecific(bool bEditorMode);
    void draw(bool bEditorMode);

	void setupRot();

    ofxBulletSphere body;

    
    bool isInsideBox(ofVec3f boxSize);

    enum BallStatus{
        BallStatusWaiting = 0,
        BallStatusPlaying,
        BallStatusGameOver
    };
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void reset();
    
    void onCollision(SimpleObject* Obj);
    
    ofVec3f getInitialPos();

    BallAttrib* getBallAttr();

	void stop(bool bStopBall);

	
	BallState GetBallState();
	void SetBallState(BallState enState);
private:

    void setupBody(SimpleObjectAttrib &Attributes);
    void setupLookStyle(SimpleObjectAttrib &Attributes);
    void setupAnimations(SimpleObjectAttrib &Attributes);
    void setupType();

	ofVec3f m_initialPos;
	
	//shadow fake
	ofCylinderPrimitive shadow;
	
	BallState m_enBallState;
    
};

#endif /* defined(__ofxBulletEventsExample__Ball__) */
