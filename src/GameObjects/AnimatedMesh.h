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


/**
 *  AnimatedMesh is used to load models that have embedded animated meshes, or models that
 *  we want to add to the physics model using the ofxBulletTriMeshShape object
 */
class AnimatedMesh : public SimpleObject {
    
public:
    
    AnimatedMesh(vector <SimpleMission *> * _currentMissions);
	virtual void setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale);
	virtual void update(bool bEditorMode);
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
    void onCollision();
    void setDefaultZ();
    void setPosition(ofVec3f position);
	void setRotation(ofQuaternion rotation);
	void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);
    
private:
    bool bAnimate;
    ofxAssimpModelLoader	assimpPath;
    unsigned int currentVetice;
};
