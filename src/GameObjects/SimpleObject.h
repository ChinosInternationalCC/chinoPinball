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
        ShapeTypeObstacle = 6
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
	int colisionCounter;
	
	//physics vars
	//enum {Static/dynamic/Kinematic}
	float damping;
	float friction;
	
	//var status
	bool bAnimation;
	
	//var events
	//ofEvent bColision;
	bool bColision;
	
	//graphic vars
	//objDisplay mygraphicobject;
	virtual ofxBulletBaseShape* getBulletBaseShape() = 0;
    virtual string getObjectName() = 0;
	
   
};