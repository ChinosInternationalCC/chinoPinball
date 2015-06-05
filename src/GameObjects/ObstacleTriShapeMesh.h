//
//  ObstacleTriShapeMesh.h
//  chinoPinball
//
//  Created by carles on 10/05/15.
//
//

#pragma once

#include "eventComunication.h"
#include "SimpleObject.h"
#include "GameStatus.h"
#include "SoundManager.h"
#include "SimpleObject.h"


class ObstacleTriShapeMesh : public SimpleObject {
	
public:
	
	ObstacleTriShapeMesh(vector <SimpleMission *> * _currentMissions);
	
	void setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale);
	void update(bool bEditorMode);
	void draw(bool bEditorMode);
	
	void autoScalingXYZ();
	void setupRot();
	
    ofxBulletTriMeshShape body;
	ofxBulletWorldRigid *m_poWorld;
	ofMesh mesh, omesh;
	ofxBulletWorldRigid *world;
	ofVec3f         initScale;
	
	
    ofxBulletTriMeshShape* getBulletBaseShape();

	string getObjectName();
	
    void onCollision();
	void setDefaultZ();
	void setPosition(ofVec3f position);
	void setRotation(ofQuaternion rotation);
	void setAngle2Rotate(float angle2rot, ofVec3f axis2rot);
	
	void setDefaultPostion();
	
protected:
	virtual void setupSpecific();
	virtual void updateSpecific(bool bEditorMode);
	virtual void onCollisionSpecific();
	
	unsigned int currentVetice;
	float anisotropy;
	ofFbo fbo, fboSphere;
};
