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


enum shapeType{
	ShapeTypeBall = 0,
	ShapeTypeSimpleBox,
	ShapeTypeSpring,
	ShapeTypeLever,
	ShapeTypeContainer
};

 
class SimpleObject {
    
public:
	
	SimpleObject();
	//virtual  ~SimpleObject();
	
	virtual void setup(ofxBulletWorldRigid &world);
	virtual void update();
	virtual void draw();
    
	//general vars
	int idobject;
    ofMatrix4x4 worldposition;
	ofVec3f centroide;
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
	
	
   
};