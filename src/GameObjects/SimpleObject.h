//
//  SimpleObject.h
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxBullet.h"
//#include "objDisplay.h"
#include "ofxAssimpModelLoader.h"


class SimpleObject {
    
public:

	
	SimpleObject();
	//virtual  ~SimpleObject();
	
    enum shapeType{
        ShapeTypeBall = 0,
        ShapeTypeSimpleBox = 1,
        ShapeTypeSpring = 2,
        ShapeTypeLever = 3,
        ShapeTypeContainer = 4,
        ShapeTypeHammer = 5,
        ShapeTypeObstacle = 6,
        ShapeTypeBounds = 7
    };
    
    //ofxBulletCustomShape	body;
    shapeType type;
    
	virtual void setup(ofxBulletWorldRigid &world, ofVec3f _pos);
	virtual void update()=0;
	virtual void draw()=0;
    
	//general vars
	int idobject;
    ofMatrix4x4 worldposition;
	ofVec3f position;
	bool bvisible;

    int color;
    
	int highlightColor;
    int highlightTime;
	
	//physics vars
	//enum {Static/dynamic/Kinematic}
	float damping;
	float friction;
	
	//var status
	bool bAnimation;
	
	//var events
	//ofEvent bColision;
	bool bColision;
	int  collisionTime;
	int colisionCounter;
    
    ofVec3f scale, last_scale;  // if we load a 3D model this variable should store the scale factors
	float scaleXyz, last_scaleXyz;
                    // with the correct values so that our model nicely fits inside the Scenario
    string ModelPath; //if we load an external 3D Model this variable should hold the path of the
                      // model
    int ObjectId; //this should be a unique identificator for each object that we have on the scenario
    void SetObjectId(int objId);
    int GetObjectId(void);
	//graphic vars
	//objDisplay mygraphicobject;
	virtual ofxBulletBaseShape* getBulletBaseShape() = 0;
    virtual string getObjectName() = 0;
    virtual void onCollision() = 0;
    virtual void setDefaultZ() = 0;
    virtual void setPosition(ofVec3f position) = 0;
   
};