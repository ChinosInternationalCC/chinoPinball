//
//  Obstacle.h
//  chinoPinball
//
//  Created by Angel on 02/02/14.
//
//

#pragma once

#include "eventComunication.h"
#include "SimpleObject.h"
#include "GameStatus.h"
#include "SoundManager.h"
#include "SimpleObject.h"

class ObstacleAttrib : public SimpleObjectAttrib{
public:
    inline ObstacleAttrib(ofVec3f _position,
                       float _damping,
                       float _friction,
                       float _mass,
                       float _restitution,
                       string _url,
                       ofVec3f _ModelScale);
    string url;
    ofVec3f ModelScale;
};

inline ObstacleAttrib::ObstacleAttrib(ofVec3f _position,
                                float _damping,
                                float _friction,
                                float _mass,
                                float _restitution,
                                string _url,
                                ofVec3f _ModelScale) :
SimpleObjectAttrib(_position,
                   _damping,
                   _friction,
                   _mass,
                   _restitution){
    url = _url;
    ModelScale = _ModelScale;
}


class Obstacle : public SimpleObject {

public:

    Obstacle(vector <SimpleMission *> * _currentMissions);
	
    void setup(ofxBulletWorldRigid &world,
               SimpleObjectAttrib *Attributes
               /*ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale*/);
    void draw(bool bEditorMode);
	
	void setupRot();
	
	ofxBulletCustomShape	body;
    

    ofxBulletBaseShape* getBulletBaseShape();
    virtual string getObjectName();
    
    void onCollision();
	void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);

    
    
    ObstacleAttrib* getObstacleAttr();
    
protected:
    virtual void setupSpecific();
    virtual void updateSpecific(bool bEditorMode);
    virtual void onCollisionSpecific();
    
private:
    void setupBody(SimpleObjectAttrib &Attributes);
    void setupLookStyle(SimpleObjectAttrib &Attributes);
    void setupAnimations(SimpleObjectAttrib &Attributes);
    void setupType();
};
