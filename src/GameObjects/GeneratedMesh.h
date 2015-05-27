//
//  GeneratedMesh.h
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
 *  GeneratedMesh is based on the ofxBullet mesh example and is a mesh built in code 
 *  that moves(like the waves of the sea)
 */
class GeneratedMesh : public SimpleObject {
    
public:
    
    GeneratedMesh(vector <SimpleMission *> * _currentMissions);
	virtual void setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale);
	virtual void update(bool bEditorMode);
	virtual void draw(bool bEditorMode);
	
	void autoScalingXYZ();
	void setupRot();
	
	//ofxBulletCustomShape	body;
    ofxBulletTriMeshShape body;
	ofxBulletWorldRigid *world;
	
	ofVec3f         initScale;
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void setAnimation(bool bAnimate);
    void onCollision();
    void setDefaultZ();
    void setPosition(ofVec3f position);
	void setRotation(ofQuaternion rotation);
	void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);
	
	//Mesh stuff
	ofMesh mesh, omesh;
    
private:
	
	//Mesh stuff
    bool bAnimate;
    unsigned int currentVetice;
    
    float anisotropy;
    ofFbo fbo, fboSphere;
};
