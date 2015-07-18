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
    inline LeverAttrib(
					   string _modelData,
					   ofVec3f _position,
                      float _damping,
                      float _friction,
                      float _mass,
                      float _restitution,
                      ofVec3f _ModelScale,
                      int _direction);
    string url;
    int direction; // rotation direction: 1 - clockwise, 0 - counter clockwise
    
};

inline LeverAttrib::LeverAttrib(string _modelData,
								ofVec3f _position,
                                float _damping,
                                float _friction,
                                float _mass,
                                float _restitution,
                                ofVec3f _ModelScale,
                                int _direction) :
        SimpleObjectAttrib(_modelData,
				   _position,
                   _damping,
                   _friction,
                   _mass,
                   _restitution,
				   _ModelScale){
			
            direction = _direction;
    
}

class Lever : public SimpleObject {
    
public:
    
    Lever(vector <SimpleMission *> * _currentMissions);
	void setup(ofxBulletWorldRigid &world, SimpleObjectAttrib *Attributes);
    
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
    
    void onCollision(int ObjId);

    LeverAttrib* getLeverAttr();
    
private:
    void setupBody(SimpleObjectAttrib &Attributes);
    void setupLookStyle(SimpleObjectAttrib &Attributes);
    void setupAnimations(SimpleObjectAttrib &Attributes);
    void setupType();
    
};
