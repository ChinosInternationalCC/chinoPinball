//
//  AnimatedObject.h
//  chinoPinball
//
//  Created by Ovidiu on 16/4/15.
//
//

#pragma once

#include "eventComunication.h"
#include "SimpleObject.h"
#include "GameStatus.h"
#include "SoundManager.h"
#include "SimpleObject.h"

class AnimatedMeshAttrib : public SimpleObjectAttrib{
public:
	inline AnimatedMeshAttrib(string _modelPath,
					   ofVec3f _position,
						  float _damping,
						  float _friction,
						  float _mass,
						  float _restitution,
						  ofVec3f _ModelScale);

};

inline AnimatedMeshAttrib::AnimatedMeshAttrib(string  _modelPath,
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


/**
 *  AnimatedMesh is used to load models that have embedded animated meshes, or models that
 *  we want to add to the physics model using the ofxBulletTriMeshShape object
 */
class AnimatedMesh : public SimpleObject {
	
public:
    
    AnimatedMesh(vector <SimpleMission *> * _currentMissions);
	virtual void setup(ofxBulletWorldRigid &world,  SimpleObjectAttrib *Attributes);
    void updateSpecific(bool bEditorMode);
	virtual void draw(bool bEditorMode);
	
	void autoScalingXYZ();
	void setupRot();
	
	//ofxBulletCustomShape	body;
    ofxBulletTriMeshShape body;
	ofVec3f         initScale;
    ofMesh mesh;
    ofxBulletWorldRigid *world;
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void setAnimation(bool bAnimate);
    void onCollision(int ObjId);
	void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);
	AnimatedMeshAttrib* getAnimatedMeshAttr();
	
	
private:
    bool bAnimate;
    ofxAssimpModelLoader	assimpPath;
    unsigned int currentVetice;
	
	void setupBody(SimpleObjectAttrib &Attributes);
	void setupLookStyle(SimpleObjectAttrib &Attributes);
	void setupAnimations(SimpleObjectAttrib &Attributes);
	void setupType();
	
};
