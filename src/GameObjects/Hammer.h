//
//  Hammer.h
//  chinoPinball
//
//  Created by Ovidiu on 12/01/14.
//
//

#pragma once

#include "SimpleObject.h"
#include "eventGame.h"

/*
 Objeto que se usa para empujar la bola (en el estado initial o para los objectos containers)

*/

class Hammer : public SimpleObject {
    
public:
    Hammer(vector <SimpleMission *> * _currentMissions);
	virtual void setup(ofxBulletWorldRigid &world, ofVec3f pos);
	virtual void update(bool bEditorMode);
	virtual void draw(bool bEditorMode);
	void move(float height);
	
	void setupRot();
    
	ofxBulletBox	body;
    
	float lowerLimit;
	float upperLimit;
    float speed;
    
    bool isKeyPressed;
    void onMoveEvent();
    void onReleaseEvent();
    
    ofxBulletBaseShape* getBulletBaseShape();
    string getObjectName();
    
    void onCollision();
    void setDefaultZ();
    void setPosition(ofVec3f position);
	void setRotation(ofQuaternion rotation);
	
	
	//Event launch hammer
	bool bLaunch = true;
    
 /*
    energy ( float )
    Shape ( )
    ofVec3f startmov
    ofVec3f endmov
    int duration
*/
    
    /*
     setup(ofVec3f startPoint, ofVec3f EndPoint, enum Shape, ofVec3f Size, worldPos )
     start(Timer t) //
     checkDistance2ball(int idBall);

     */
    
};
