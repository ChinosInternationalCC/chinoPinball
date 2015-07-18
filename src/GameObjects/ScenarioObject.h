//
//  ScenarioObject.h
//  chinoPinball
//
//  Created by Carles Gutierrez on 17/07/15.
//
//

#pragma once

#include "eventComunication.h"
#include "SimpleObject.h"
#include "GameStatus.h"
#include "SoundManager.h"

class ScenarioObjectAttrib : public SimpleObjectAttrib{
public:
    inline ScenarioObjectAttrib(string _modelPath,
					   ofVec3f _position,
                       float _damping,
                       float _friction,
                       float _mass,
                       float _restitution,
                       ofVec3f _ModelScale);
    
};

inline ScenarioObjectAttrib::ScenarioObjectAttrib(string  _modelPath,
								ofVec3f _position,
                                float _damping,
                                float _friction,
                                float _mass,
                                float _restitution,
                                ofVec3f _ModelScale) :
SimpleObjectAttrib(_modelPath,
				   _position,
                   _damping,
                   _friction,
                   _mass,
                   _restitution,
				   _ModelScale){
}


class ScenarioObject : public SimpleObject {

public:

    ScenarioObject(vector <SimpleMission *> * _currentMissions);
	
    void setup(ofxBulletWorldRigid &world,
               SimpleObjectAttrib *Attributes
               /*ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale*/);
    void draw(bool bEditorMode);
	
	void setupRot();
	
	ofxBulletCustomShape	body;
    

    ofxBulletBaseShape* getBulletBaseShape();
    virtual string getObjectName();
    
    void onCollision(int ObjId);
	void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);

    
    
    ScenarioObjectAttrib* getScenarioObjectAttr();
    
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
