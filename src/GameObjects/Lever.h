//
//  Lever.h
//  chinoPinball
//
//  Created by Kuba on 03/01/14.
//
//

#pragma once

#include "SimpleObject.h"

class LeverAttrib : public SimpleObjectAttrib{
public:
    inline LeverAttrib(ofVec3f _position,
                      float _damping,
                      float _friction,
                      float _mass,
                      float _restitution,
                      string _url,
                      ofVec3f _ModelScale,
                      int _direction);
    string url;
    ofVec3f ModelScale;
    int direction; // rotation direction: 1 - clockwise, 0 - counter clockwise
    
};

inline LeverAttrib::LeverAttrib(ofVec3f _position,
                                float _damping,
                                float _friction,
                                float _mass,
                                float _restitution,
                                string _url,
                                ofVec3f _ModelScale,
                                int _direction) :
        SimpleObjectAttrib(_position,
                   _damping,
                   _friction,
                   _mass,
                   _restitution){
            url = _url;
            ModelScale = _ModelScale;
            direction = _direction;
    
}

class Lever : public SimpleObject {
    
public:
    
    Lever(vector <SimpleMission *> * _currentMissions);
	void setup(ofxBulletWorldRigid &world, SimpleObjectAttrib *Attributes);
    
	void update(bool bEditorMode);
    void updateSpecific(bool bEditorMode);
	void draw(bool bEditorMode);
	void rotate(float degrees);
	
	void setupRot();
    
	ofxBulletCustomShape	body;
    
    
    btQuaternion    rotationLever;
    
    float angle; // degrees
	float lowerLimit;
	float upperLimit;
    float speed, speedUp, speedDown;
    float axisX;
    
    bool isKeyPressed;
    void onMoveEvent();
    void onReleaseEvent();
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void onCollision();

    LeverAttrib* getLeverAttr();
    
private:
    void setupBody(SimpleObjectAttrib &Attributes);
    void setupLookStyle(SimpleObjectAttrib &Attributes);
    void setupAnimations(SimpleObjectAttrib &Attributes);
    void setupType();
    
};
