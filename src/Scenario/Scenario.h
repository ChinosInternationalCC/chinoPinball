//
//  Scenario.h
//  ofxBulletEventsExample
//
//  Created by Kuba on 28/12/13.
//
//  Description: Responsable por inicializar y controlar los elementos de un escenario del juego.
//

#pragma once

#include "ofxBullet.h"

#include "Ball.h"
#include "Lever.h"
#include "Hammer.h"

class Scenario {
    
public:
	void setup(ofxBulletWorldRigid &world);
	void update();
	void draw();
    void loadBasicScenario(ofxBulletWorldRigid &world, ofVec3f _pos);
	
    ofxBulletWorldRigid *     world;
    
    Ball                      m_Ball,m_Ball2;
    Lever                   leverLeft;
    Lever                   leverRight;
    Hammer                   m_Hammer;
	
	//basic World
	vector <ofxBulletBox*>		bounds;
	float						boundsWidth;
};