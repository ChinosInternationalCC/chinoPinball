//
//  Bounds.h
//  chinoPinball
//
//  Created by Angel Muc on 20/06/14.
//
//

#pragma once

#include "eventComunication.h"
#include "SimpleObject.h"
#include "GameStatus.h"
#include "SoundManager.h"
#include "SimpleObject.h"


class Bounds : public SimpleObject {
    
public:
    
	virtual void setup(ofxBulletWorldRigid &world, ofVec3f position, string url, ofVec3f ModelScale);
	virtual void update(bool bEditorMode);
	virtual void draw(bool bEditorMode);
	
	void autoScalingXYZ();
	//void autoScalingXYZ();
    
	ofxBulletCustomShape	body;
	ofxAssimpModelLoader	assimpModel;
    ofMaterial				material;
    ofMesh                  assimpModelMesh;
    
    //vector<bool>				bColliding;
    
	
    
	ofVec3f         initScale;
    
    btQuaternion    rotation;
    
    float angle; // degrees
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void onCollision();
    void setDefaultZ();
    void setPosition(ofVec3f position);
    
};
