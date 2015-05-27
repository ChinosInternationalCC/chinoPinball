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
 *  The Animate Object should be used to load models that have animated meshes embedded
 *  The phisics object used is of type ofxBulletCustomShape and we observed that this kind of 
 *  object doesn't work very well with models that have negative angles. If you want to load 
 *  this kind of model you might also take a look at AnimatedMesh that adds the model to the 
 *  physics model using the ofxBulletTriMeshShape
 */
class AnimatedObject : public SimpleObject {
    
public:
    
    
    AnimatedObject(vector <SimpleMission *> * _currentMissions);
	virtual void setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale);
    void updateSpecific(bool bEditorMode);
	virtual void draw(bool bEditorMode);
	
	void autoScalingXYZ();
	void setupRot();
	
	ofxBulletCustomShape	body;
    
	ofVec3f         initScale;
    
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void setAnimation(bool bAnimate);
    void onCollision();
	void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);

private:
    bool bAnimate;
    ofxAssimpModelLoader	assimpPath;
    unsigned int currentVetice;
};
